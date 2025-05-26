function res = raiz(X)


    if X < 0
        error('Entrada inválida: não é possível calcular a raiz quadrada de um número negativo.');
    end

    % Casos triviais
    if X == 0 || X == 1
        res = X;
        return;
    end

    % Valor inicial
    x0 = X / 2;


    tol = 1e-6;
    max_iter = 100;


    iter = 0;
    erro = inf;


    while erro > tol && iter < max_iter
        x1 = (x0 + X / x0) / 2;
        erro = abs(x1 - x0);
        x0 = x1;
        iter = iter + 1;
    end


    res = x0;
end

