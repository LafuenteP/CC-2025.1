function x = resolver_x_newton(y, x0, tol, max_iter)

    iter = 0;
    erro = inf;
    x = x0;

    while erro > tol && iter < max_iter
        f = x^2 * y - x * y^2 - 6;
        df = 2 * x * y - y^2;
        if df == 0
            error('Derivada zero - método falha');
        end

        x_new = x - f / df;
        erro = abs(x_new - x);
        x = x_new;
        iter = iter + 1;
    end

    if iter == max_iter
        warning('Máximo de iterações atingido!');
    end
end

