function [U,nIters,eTime] = PCAGM(trainData,generalizedMean,nFeatsPCA,p)
% This function is used to compute the projection matrix U by performing
% the principal component analysis using generalized mean, which is
% described in:
%       Jiyong Oh and Nojun Kwak, "Generalized mean for robust principal
%       component analysis," Patterm Recognition, vol. 54, pp. 116-127,
%       June 2016.
% The first input arguments 'trainData' is a 2-dim. matrix where each row
% vector corresponds to each data sample.
% The second argument 'generalizedMean' is the generalized sample mean,
% which is described in the above paper.
% The third argument 'nFeatsPCA' is the dimension of the subspace or the
% projected space.
% The last argument 'p' is the intrinsic parameter of the generalized mean.
% Details can be referred as to the above paper.
% This code is written by Jiyong Oh. Nov. 22, 2015.

t0 = clock;

nMaxIter = 100;
threDiff = 10^(-5);
ratio = 0.01;

U = PCA(trainData,nFeatsPCA);

nTrain = size(trainData,1);
meanMat = repmat(generalizedMean,[nTrain,1]);
trainDataZM = trainData - meanMat;

residue = ComptResidualErrors(trainDataZM,U);
objFunc = sum(residue.^(p));
%display(['p=' num2str(p) ',  nFeats=' num2str(nFeatsPCA) ',  Iteration Index=0,  ObjFuncValue=' num2str(ObjFunc) ]);

minResidue = min(residue);
eps = ratio * minResidue;

flag = 0;
index = 0;
while flag == 0
    index = index + 1;
    
    U_Before = U;
    objFunc_Before = objFunc;
    
    residue = residue + eps*ones(size(residue));
    alphas = residue.^(p-1);
    
    A = sqrt(diag(alphas));
    S = trainDataZM' * A;
    [eigVectors,~,~] = svd(S,0);
    U = eigVectors(:,1:nFeatsPCA);
    %disp(S)
    
    residue = ComptResidualErrors(trainDataZM,U);
    objFunc = sum(residue.^(p));
    
    %display(['p=' num2str(p) ',  nFeats=' num2str(nFeatsPCA) ',  Iteration Index=' num2str(index) ',  ObjFuncValue=' num2str(objFunc) ]);
    
    if objFunc_Before-objFunc < threDiff
        flag = 1;
    elseif objFunc >= objFunc_Before
        flag = 1;
        U = U_Before;
    elseif index >= nMaxIter
        flag = 1;    
    end       
    
end
nIters = index;

eTime = etime(clock,t0);

end

function errors = ComptResidualErrors(trainDataZM,U)

trainDataProj =  trainDataZM * U;
disp(trainDataProj * trainDataProj')
R = (trainDataZM*trainDataZM') - (trainDataProj*trainDataProj');
disp(trainDataProj);
disp(U);
disp('Jaja saludos');
errors = diag(R);

end

function [W_PCA,eTime] = PCA(trainData,nFeatsPCA)

t0 = clock;

[nTrain,nVar] = size(trainData);
meanTrain = mean(trainData);
meanMat = repmat(meanTrain,[nTrain,1]);
if nTrain < nVar
    S = (trainData-meanMat)*(trainData-meanMat)'/nTrain;
    U = diagonal(S);
    W = U(:,1:nFeatsPCA);
    W_PCA = (trainData-meanMat)'*W;
    for k=1:nFeatsPCA
        W_PCA(:,k) = W_PCA(:,k) / sqrt(W_PCA(:,k)'*W_PCA(:,k));
    end
else
    S = (trainData-meanMat)'*(trainData-meanMat)/nTrain;
    W = diagonal(S);
    W_PCA = W(:,1:nFeatsPCA);
end

eTime = etime(clock,t0);

end

function [Vectors,Values] = diagonal(M)
% the input argument M should be an n by n square matrix.
    [Vectors,D] = svd(M);
    d_1D = diag(D);
    Values = d_1D.^2;
end
