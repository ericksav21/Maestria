# -*- coding: utf-8 -*-

import os.path, glob
import shutil
import skimage, skimage.data
import skimage.io as io
import numpy as np
import tensorflow as tf
from skimage.color import rgb2lab

class ColorNet(object):
	def __init__(self, phase, no_classes):
		self.phase = phase
		self.no_classes = no_classes
		# W = tf.get_variable("W", shape=[784, 256], initializer=tf.contrib.layers.xavier_initializer())
		self._config = {
			# Low level features network
			'low_1_w': tf.Variable(tf.truncated_normal([3, 3, 1, 64]), name = 'low_1_w'),
			'low_1_b': tf.Variable(tf.truncated_normal([64]), name = 'low_1_b'),
			'low_2_w': tf.Variable(tf.truncated_normal([3, 3, 64, 128]), name = 'low_2_w'),
			'low_2_b': tf.Variable(tf.truncated_normal([128]), name = 'low_2_b'),

			'low_3_w': tf.Variable(tf.truncated_normal([3, 3, 128, 128]), name = 'low_3_w'),
			'low_3_b': tf.Variable(tf.truncated_normal([128]), name = 'low_3_b'),
			'low_4_w': tf.Variable(tf.truncated_normal([3, 3, 128, 256]), name = 'low_4_w'),
			'low_4_b': tf.Variable(tf.truncated_normal([256]), name = 'low_4_b'),

			'low_5_w': tf.Variable(tf.truncated_normal([3, 3, 256, 256]), name = 'low_5_w'),
			'low_5_b': tf.Variable(tf.truncated_normal([256]), name = 'low_5_b'),
			'low_6_w': tf.Variable(tf.truncated_normal([3, 3, 256, 512]), name = 'low_6_w'),
			'low_6_b': tf.Variable(tf.truncated_normal([512]), name = 'low_6_b'),

			# Middle level features network
			'mid_1_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'mid_1_w'),
			'mid_1_b': tf.Variable(tf.truncated_normal([512]), name = 'mid_1_b'),
			'mid_2_w': tf.Variable(tf.truncated_normal([3, 3, 512, 256]), name = 'mid_2_w'),
			'mid_2_b': tf.Variable(tf.truncated_normal([256]), name = 'mid_2_b'),

			# Global Conv level features network
			'glo_1_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_1_w'),
			'glo_1_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_1_b'),
			'glo_2_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_2_w'),
			'glo_2_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_2_b'),
			'glo_3_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_3_w'),
			'glo_3_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_3_b'),
			'glo_4_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_4_w'),
			'glo_4_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_4_b'),

			# Global FC  # input, output are reversed.
			'glo_5_w': tf.Variable(tf.truncated_normal([7 * 7 * 512, 1024]), name = 'glo_5_w'),
			#'glo_5_b': tf.Variable(tf.truncated_normal([1024]), name = 'glo_5_b'),
			'glo_5_b': 1024,
			'glo_6_w': tf.Variable(tf.truncated_normal([1024, 512]), name = 'glo_6_w'),
			#'glo_6_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_6_b'),
			'glo_6_b': 512,
			'glo_7_w': tf.Variable(tf.truncated_normal([512, 256]), name = 'glo_7_w'),
			#'glo_7_b': tf.Variable(tf.truncated_normal([256]), name = 'glo_7_b'),
			'glo_7_b': 256,

			# Classification neural network
			#'class_1_b': tf.Variable(tf.truncated_normal([256]), name = 'glo_1_b'),
			'class_1_b': 256,
			#'class_2_b': tf.Variable(tf.truncated_normal([no_classes]), name = 'glo_2_b'),
			'class_2_b': no_classes,

			# Fusion Network
			'fuse_1_w': tf.Variable(tf.truncated_normal([512, 256]), name = 'fuse_1_w'),
			'fuse_1_b': tf.Variable(tf.truncated_normal([256]), name = 'fuse_1_b'),

			# Colorization network
			'col_1_w': tf.Variable(tf.truncated_normal([3, 3, 256, 128]), name = 'col_1_w'),
			'col_1_b': tf.Variable(tf.truncated_normal([128]), name = 'col_1_b'),

			'col_2_w': tf.Variable(tf.truncated_normal([3, 3, 128, 64]), name = 'col_2_w'),
			'col_2_b': tf.Variable(tf.truncated_normal([64]), name = 'col_2_b'),
			'col_3_w': tf.Variable(tf.truncated_normal([3, 3, 64, 64]), name = 'col_3_w'),
			'col_3_b': tf.Variable(tf.truncated_normal([64]), name = 'col_3_b'),

			'col_4_w': tf.Variable(tf.truncated_normal([3, 3, 64, 32]), name = 'col_4_w'),
			'col_4_b': tf.Variable(tf.truncated_normal([32]), name = 'col_4_b'),
			'col_5_w': tf.Variable(tf.truncated_normal([3, 3, 32, 2]), name = 'col_5_w'),
			'col_5_b': tf.Variable(tf.truncated_normal([2]), name = 'col_5_b')
		}
		self.one_stride = [1, 1, 1, 1]
		self.two_stride = [1, 2, 2, 1]
		self.logits = None

	def set_phase(self, phase):
		self.phase = phase

	def _set_conv2d_layer(self, input, f, b, s, name = None):
		conv = tf.nn.conv2d(input, filter = f, strides = s, padding = "SAME", name = name)
		bn = tf.nn.bias_add(conv, b)
		bn = tf.contrib.layers.batch_norm(bn, center = True, scale = True, is_training = self.phase)
		bn = tf.nn.relu(bn)
		return bn

	def _set_fc_layer(self, x, b, name = None):
		dense = tf.layers.dense(inputs = x, units = b, activation = tf.nn.relu, use_bias = True, name = name)
		dense = tf.contrib.layers.batch_norm(dense, center = True, scale = True, is_training = self.phase)
		return dense

	#Capa de fusión propuesta por el paper
	def _set_fusion_layer(self, mid_feat, global_feat, name = "fused_activation"):
		# [batch, 256] -> [batch, 1, 1, 256]
		padded_global = tf.expand_dims(tf.expand_dims(global_feat, 1), 1)

		# [batch, 1, 1, 256] -> [batch, H/8, W/8, 256 channels]
		padded_global = tf.tile(padded_global, [1, tf.shape(mid_feat)[1], tf.shape(mid_feat)[2], 1])

		# [batch, H/8, W/8, 256] x [batch, H/8, W/8, 256] -> [batch, H/8, W/8, 512]
		fused_input = tf.concat([mid_feat, padded_global], axis = 3)

		# [batch, H/8, W/8, 512] -> [batch * H/8 * W/8, 512]
		fused_input = tf.reshape(fused_input, [-1, 512])

		# [batch * H/8 * W/8, 512] x [512, 256] -> [batch * H/8 * W/8, 256]
		fused_activation = tf.add(tf.matmul(fused_input, self._config['fuse_1_w']), self._config['fuse_1_b'], name = name)
		fused_activation = tf.contrib.layers.batch_norm(fused_activation, center = True, scale = True, is_training = self.phase)

        # [batch * H/8 * W/8, 256] -> [batch, H/8, W/8, 256]
		fused_activation = tf.reshape(fused_activation, [
			tf.shape(mid_feat)[0],
			tf.shape(mid_feat)[1],
			tf.shape(mid_feat)[2], -1])

		return fused_activation

	def _up_sample(self, x):
		return tf.image.resize_images(x,
			[2 * tf.shape(x)[1],
			2 * tf.shape(x)[2]],
			method = tf.image.ResizeMethod.NEAREST_NEIGHBOR)

	#Parte de definición del modelo
	def low_level_feat_nn(self, x):
		ll_logits = self._set_conv2d_layer(x, self._config['low_1_w'], self._config['low_1_b'], self.two_stride, name = 'low_c1')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_2_w'], self._config['low_2_b'], self.one_stride, name = 'low_c2')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_3_w'], self._config['low_3_b'], self.two_stride, name = 'low_c3')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_4_w'], self._config['low_4_b'], self.one_stride, name = 'low_c4')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_5_w'], self._config['low_5_b'], self.two_stride, name = 'low_c5')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_6_w'], self._config['low_6_b'], self.one_stride, name = 'low_c6')

		return ll_logits

	def mid_level_feat_nn(self, x):
		ml_logits = self._set_conv2d_layer(x, self._config['mid_1_w'], self._config['mid_1_b'], self.one_stride, name = 'middle_c1')
		ml_logits = self._set_conv2d_layer(ml_logits, self._config['mid_2_w'], self._config['mid_2_b'], self.one_stride, name = 'middle_c2')

		return ml_logits

	def global_level_feat_nn(self, x):
		gl_logits = self._set_conv2d_layer(x, self._config['glo_1_w'], self._config['glo_1_b'], self.two_stride, name = 'global_c1')
		gl_logits = self._set_conv2d_layer(gl_logits, self._config['glo_2_w'], self._config['glo_2_b'], self.one_stride, name = 'global_c2')
		gl_logits = self._set_conv2d_layer(gl_logits, self._config['glo_3_w'], self._config['glo_3_b'], self.two_stride, name = 'global_c3')
		gl_logits = self._set_conv2d_layer(gl_logits, self._config['glo_4_w'], self._config['glo_4_b'], self.one_stride, name = 'global_c4')
		
		# (batch, 4, 4, 512) -> (batch, 7 * 7 * 512)
		gl_flat = tf.reshape(gl_logits, [-1, 7 * 7 * 512], name = 'global_fl1')
		gl_logits = self._set_fc_layer(gl_flat, self._config['glo_5_b'], name = 'global_fc1')
		gl_logits_r1 = self._set_fc_layer(gl_logits, self._config['glo_6_b'], name = 'global_fc2')
		gl_logits_r2 = self._set_fc_layer(gl_logits_r1, self._config['glo_7_b'], name = 'global_fc3')

		return gl_logits_r1, gl_logits_r2

	def classification_level_feat_nn(self, x):
		class_logits = self._set_fc_layer(x, self._config['class_1_b'], name = 'class_fc1')
		#Poner una capa densa con función de activación lineal
		class_logits = tf.layers.dense(inputs = class_logits, units = self._config['class_2_b'], activation = None, use_bias = True, name = 'class_fc2')
		class_logits = tf.contrib.layers.batch_norm(class_logits, center = True, scale = True, is_training = self.phase)

		return class_logits

	def colorization_nn(self, mid_feat, global_feat):
		fusion_logits = self._set_fusion_layer(mid_feat, global_feat)
		color_logits = self._set_conv2d_layer(fusion_logits, self._config['col_1_w'], self._config['col_1_b'], self.one_stride, name = 'color_c1')
		upsampled_1 = self._up_sample(color_logits)
		color_logits = self._set_conv2d_layer(upsampled_1, self._config['col_2_w'], self._config['col_2_b'], self.one_stride, name = 'color_c2')
		color_logits = self._set_conv2d_layer(color_logits, self._config['col_3_w'], self._config['col_3_b'], self.one_stride, name = 'color_c3')
		upsampled_2 = self._up_sample(color_logits)
		color_logits = self._set_conv2d_layer(upsampled_2, self._config['col_4_w'], self._config['col_4_b'], self.one_stride, name = 'color_c4')
		
		#Esta capa se hace a mano dado que se tiene que usar otra función de activación
		color_logits = tf.nn.conv2d(color_logits, filter = self._config['col_5_w'], strides = self.one_stride, padding = "SAME", name = 'color_c5')
		color_logits = tf.nn.bias_add(color_logits, self._config['col_5_b'])
		color_logits = tf.contrib.layers.batch_norm(color_logits, center = True, scale = True, is_training = self.phase)
		color_logits = tf.nn.sigmoid(color_logits)

		color_out = self._up_sample(color_logits)

		return color_out

	def _init_model(self, x):
		x = tf.reshape(x, shape = [-1, 224, 224, 1])
		ll_logits_1 = self.low_level_feat_nn(x)

		#return ll_logits_1
		#ll_logits_2 = self.low_level_feat_nn(x)
		ml_logits = self.mid_level_feat_nn(ll_logits_1)
		class_input, gl_logits = self.global_level_feat_nn(ll_logits_1)
		class_logits = self.classification_level_feat_nn(class_input)
		color_logits = self.colorization_nn(ml_logits, gl_logits)

		return class_logits, color_logits