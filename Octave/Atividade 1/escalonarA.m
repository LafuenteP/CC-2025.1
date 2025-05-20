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
## @deftypefn {} {@var{retval} =} escalonarA (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: gilva <gilva@DESKTOP-2N7B9EM>
## Created: 2025-04-30

function res = escalonarA (A)
[m, n] = size(A);
for d = 1:min(m,n)
if A(d,d) == 0
for i = d+1:m
if A(i,d) != 0
A([d i], :) = A([i d], :);
break;
end
end
end
if A(d,d) == 0
continue;
end
A(d,:) = A(d,:) / A(d,d);
for i = d+1:m
A(i,:) = A(i,:) - A(i,d) * A(d,:);
end
end
for d = min(m,n):-1:2
for i = d-1:-1:1
A(i,:) = A(i,:) - A(i,d) * A(d,:);
end
end
res = A;
end
