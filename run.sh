#!/bin/sh

example1() {
	gcc -Wall -Wextra -ggdb -std=c11 integrator.c context.c vector.c example1.c -o example1 -lm
	(echo "== Example1 =="; ./example1 | column -L -t -s,) | less -F -S -X -K
}

example2() {
	gcc -Wall -Wextra -ggdb -std=c11 integrator.c context.c vector.c example2.c -o example2 -lm
	(echo "== Example2 =="; ./example2 | column -L -t -s,) | less -F -S -X -K
}

example3() {
	gcc -Wall -Wextra -ggdb -std=c11 integrator.c context.c vector.c example3.c -o example3 -lm
	(echo "== Example3 =="; ./example3 | column -L -t -s,) | less -F -S -X -K
}

example4() {
	gcc -Wall -Wextra -ggdb -std=c11 integrator.c context.c vector.c example4.c -o example4 -lm
	(echo "== Example4 =="; ./example4 | column -L -t -s,) | less -F -S -X -K
}

example5() {
	gcc -Wall -Wextra -ggdb -std=c11 integrator.c context.c vector.c example5.c -o example5 -lm
	(echo "== Example5 =="; ./example5 | column -L -t -s,) | less -F -S -X -K
}

echo "Examples: "
echo "	1. Integrating sin(x)              from  x = 0, PI]"
echo "	2. Integrating exp(-x^2)           from  x = [-inf, +inf]"
echo "	3. Integrating sin(x) + sin(y)     from  y = [0, 1] and x = [0, y]"
echo "	4. Integrating 1 / sqrt(1 - x * x) from  x = [0, 1]"
echo "	5. Integrating 1                   from  x = [0, R] and y = [-sqrt(R * R - x * x), sqrt(R * R - x * x)]"
echo

read -p "Select Example: " WHICH
echo

if [ $WHICH -eq 1 ]; then example1
elif [ $WHICH -eq 2 ]; then example2
elif [ $WHICH -eq 3 ]; then example3
elif [ $WHICH -eq 4 ]; then example4
elif [ $WHICH -eq 5 ]; then example5
else echo "Not Available"
fi
