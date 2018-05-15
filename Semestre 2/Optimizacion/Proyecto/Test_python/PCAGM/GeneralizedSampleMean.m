function [generalizedSampMean,eTime,nIters] = GeneralizedSampleMean(dataSamps,p)
% This function is used to compute a generalized sample mean, which is
% described in:
% Jiyong Oh and Nojun Kwak, "Generalized mean for robust principal
% component analysis," Patterm Recognition, vol. 54, pp. 116-127, June 2016.
% One of the input arguments 'dataSamps' is a 2-dim. matrix where each row
% vector corresponds to each data sample.
% The other argument 'p' is the intrinsic parameter of the generalized mean.
% Details can be referred as to the above paper.
% This code is written by Jiyong Oh. Nov. 22, 2015.

t0 = clock;
nMaxIter = 50;

meanSamps = mean(dataSamps);
meanSampsIter = meanSamps;

nSamps = size(dataSamps,1);

meanMat = repmat(meanSamps,[nSamps,1]);
dataSampsZM = dataSamps - meanMat;
objFunc = sum(diag(dataSampsZM*dataSampsZM').^(p));

index = 0;
display(['Index=' num2str(index) ', ObjFuncValue=' num2str(objFunc)]);
flag = 0;
while flag == 0
    index = index + 1;    
    
    meanSamps_Before = meanSampsIter;
    objFunc_Before = objFunc;
    
    meanMat = repmat(meanSampsIter,[nSamps,1]);
    dataSampsZM = dataSamps - meanMat;
    alphas = diag(dataSampsZM*dataSampsZM').^(p-1);
    meanSampsIter = (dataSamps' * alphas / sum(alphas))';

    meanMat = repmat(meanSampsIter,[nSamps,1]);
    dataSampsZM = dataSamps - meanMat;    
    objFunc = sum(diag(dataSampsZM*dataSampsZM').^(p));

    display(['Index=' num2str(index) ', ObjFuncValue=' num2str(objFunc)]);

    diffMeanVec = meanSampsIter - meanSamps_Before;
    diffMeanVecNorm = sqrt(diffMeanVec*diffMeanVec');

    if index >= nMaxIter
        flag = 1;
    elseif diffMeanVecNorm/sqrt(meanSampsIter*meanSampsIter')*100 < 0.01
        flag = 1;
    elseif objFunc >= objFunc_Before
        flag = 1;
        meanSampsIter = meanSamps_Before;
    end
end

generalizedSampMean = meanSampsIter;
eTime = etime(clock,t0);
nIters = index;
