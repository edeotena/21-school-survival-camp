all:
	gcc modules.c modules_db.c input_utils.c array_utils.c shared.c levels.c status_events.c -Wall -Wextra -Werror -o ../build/modules_db

test:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src/
	python3 cpplint.py *.[ch]

run: all
	leaks --quiet --atExit -- ./../build/modules_db
