function [W] = Exec()
    mu = [0, 0]
    sigma = [0.5, 0; 0, 0.5]
    p = 0.2
    %trainData = mvnrnd(mu, sigma, 100)
    %trainData = [trainData; mvnrnd([4, 4], [0.3, 0; 0, 0.3])]
    trainData = genPoints();
    disp(size(trainData))
    [W_PCA,eTime] = PCA(trainData, 2)
    [W, b, obj] = RPCA_OM(trainData', 1, 50)
    [Z, b, obj, eigv, Lambda_max, lst_U] = CRPCA_OM(trainData', 1, 1, 0.1, 1.1, 100)
    disp(lst_U)
    plot(trainData(:, 1), trainData(:, 2), '*')
    hold on
    plotv(W, '-')
    plotv(W_PCA, '--')
    hold off
    %disp(U)
end

function [Vectors,Values] = diagonal(M)
    % the input argument M should be an n by n square matrix.
    [Vectors,D] = svd(M);
    d_1D = diag(D);
    Values = d_1D.^2;
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

function [W, b, obj] = RPCA_OM(X, feature_num, NITER)
    [~, n] = size(X);

    if nargin <= 2
        NITER = 10;
    end;

    d = ones(n,1);
    obj = zeros(NITER,1);
    for iter = 1:NITER
        D = spdiags(sqrt(d),0,n,n);
        b = X*d/sum(d);
        A = X - b*ones(1,n);
        M = A*D;
        [W, ~] = svds(M, feature_num);
        B = A - W*(W'*A);
        Bi = sqrt(sum(B.*B,1)+eps)';
        d = 0.5./(Bi);   
        obj(iter) = sum(Bi);
    end
end

function [Z,b,obj,eigv,Lambda_max, lst_U] = CRPCA_OM(X, r, isbias, mu, rho, NITER)

	[dim, n] = size(X);
	H = eye(n) - 1/n*ones(n);

	if nargin <= 3
	    mu = 0.1;
	    rho = 1.1;
	    NITER = 100;
	end;

	Lambda = zeros(dim, n);
	E = rand(dim, n);

	obj = zeros(NITER,1);
    lst_U = 0;
	for iter = 1:NITER
	    
	    inmu = 1/mu;
	    X1 = X - E + inmu*Lambda;
	    r1 = r*inmu;
	    if isbias == 1
		b = mean(X1,2);
		XH = X1*H;
		[U, A, V] = svd(XH,'econ');
        lst_U = U;
	    else
		b = zeros(dim,1);
		[U, A, V] = svd(X1,'econ');
        lst_U = U;
	    end;
	    a = diag(A);
	    a1 = max(a-r1, 0);
	    Z = U*diag(a1)*V';
	    
	    X2 = X - b*ones(1,n) - Z + inmu*Lambda;
	    r2 = inmu;
	    for i=1:n
		x = X2(:,i);
		aa = norm(x);
		if aa > r2
		    E(:,i) = (1-r2/aa)*x;
		else
		    E(:,i) = 0;
		end;
	    end;
	    Lambda = Lambda + mu*(X - b*ones(1,n) - Z - E);
	    mu = min(10^8,rho*mu);

	    % compute objective value
	    if isbias == 1
		XHZ = XH-Z;
	    else
		XHZ = X-Z;
	    end;
	    err = sum(sqrt(sum(XHZ.^2)));
	    obj(iter) = err + r*sum(a1);
	end;
	eigv = a1;

	Lambda_max = max(abs(Lambda(:)))/mu;
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
    trainData = [trainData; mvnrnd([2, 2], [0.3, 0; 0, 0.3], 4)];
end
