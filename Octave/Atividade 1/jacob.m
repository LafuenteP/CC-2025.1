## Copyright (C) 2025 gilva
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} jacob (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Lafuente Paulino
## Created: 2025-04-30

function res = jacob(A, b, x0)
% Aproximação inicial: x0 = [x; y] por exemplo [2; 1]
x = x0(1);
y = x0(2);
tol = 1e-6;
max_iter = 1000;
iter = 0;

while iter < max_iter
iter += 1;
x1 = sqrt((y + 46)/5);
y1 = sqrt((17 - 2*x)/11);
if !isreal(x1) || !isreal(y1)
printf("Iteração gerou número complexo. Tente outra estimativa.\n");
res = [NaN; NaN];
return
end
if abs(x1 - x) < tol && abs(y1 - y) < tol
break
end
x = x1;
y = y1;
end

res = [x; y];
printf("Número de iterações: %d\n", iter);
endfunction


