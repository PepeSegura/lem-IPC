#include "GAME.h"

char    parser(int argc, char **argv)
{
    if (argc != 2)
        ft_error("Invalid number of arguments.");
    if (ft_strlen(argv[1]) > 1 || ft_isalpha(argv[1][0]) == 0)
        ft_error("Player team must be a letter.");
    return (argv[1][0]);
}
