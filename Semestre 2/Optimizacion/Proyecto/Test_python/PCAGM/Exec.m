function [U] = Exec()
    mu = [0, 0]
    sigma = [0.5, 0; 0, 0.5]
    p = 0.2
    %trainData = mvnrnd(mu, sigma, 100)
    %trainData = [trainData; mvnrnd([4, 4], [0.3, 0; 0, 0.3])]
    %trainData = genPoints()
    trainData = [4.26626625e-01, 1.56283527e-01;
				 6.59907107e-01, 5.65598772e-02;
				 5.51226781e-01, 6.67020756e-02;
				 9.43067169e-02, 1.31892281e-01;
				 1.72283828e-01, 2.02385756e-01;
				 5.61692330e-01, 9.67861317e-02;
				 3.39888746e-02, 2.50193632e-02;
				 1.08184376e-01, 1.40396619e-01;
				 4.07350906e-01, 1.90069896e-01;
				 1.62481740e-01, 2.77166196e-01;
				 9.71744212e-02, 1.13628924e-01;
				 2.82885520e-02, 6.50027667e-02;
				 4.35261216e-01, 1.94798811e-01;
				 2.18142741e-01, 1.33335477e-01;
				 1.02873443e-01, 1.39007032e-01;
				 2.37791407e-01, 1.20676655e-01;
				 2.41890881e-01, 2.02274347e-03;
				 3.82936607e-01, 2.15804912e-01;
				 1.24889117e-01, 1.46707311e-01;
				 4.50116919e-01, 2.42119830e-01;
				 3.15527909e+00, 3.19645919e+00;
				 3.26713497e+00, 3.01798668e+00]
    [generalizedSampMean,eTime,nIters] = GeneralizedSampleMean(trainData, p)
    [W_PCA,eTime] = PCA(trainData, 2)
    [U,nIters,eTime] = PCAGM(trainData, generalizedSampMean, 2, p)
    %disp(generalizedSampMean)
    %disp(mean(trainData))
    %plot(trainData(:, 1), trainData(:, 2), '*')
    %hold on
    %plotv(U, '-')
    %plotv(W_PCA, '--')
    %hold off
    %disp(U)
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

function [trainData] = genPoints()
    trainData = zeros(100, 2)
    cx1 = 0.0
	cy1 = 0.0
	cnt = 1
    while 1
        xi = normrnd(1, 1)
        yi = normrnd(1, 1)
        if ((xi - cx1).^2 / 0.5) + ((yi - cy1).^2 / 0.1) <= 1
            trainData(cnt, 1) = xi
            trainData(cnt, 2) = yi
            cnt = cnt + 1
        end
        if cnt == 101
            break
        end
    end
    trainData = [trainData; mvnrnd([2, 2], [0.3, 0; 0, 0.3], 1)];
end