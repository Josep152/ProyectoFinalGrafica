#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include <string>
#include<vector>
#pragma warning(disable:4996)
#include "../utils.h"

std::string solver(char* cube);
std::vector<std::string> get_solution(std::string Cube);
std::string format_solution(std::vector<std::string>);
std::vector<std::string> string_to_vector(std::string);

std::string solver(char* cube) {
    char* facelets = cube;
    char* sol = solution(
        facelets,
        24,
        1000,
        0,
        "cache"
    );
    if (sol == NULL)return "No answer";
    std::string answer;
    for (int i = 0; sol[i] != '\0'; ++i) {
        answer.push_back(sol[i]);
    }
    return answer;
}

std::vector<std::string> get_solution(std::string Cube) {
    char* cube = new char[(int)Cube.size()];
    for (int i = 0; i < (int)Cube.size(); ++i) {
        cube[i] = Cube[i];
    }
    std::string solution = solver(cube);
    std::vector<std::string> the_solution;
    std::string temp = "";
    for (int i = 0; i < (int)solution.size(); ++i) {
        if (solution[i] == ' ') {
            the_solution.push_back(temp);
            temp = "";
        }
        else {
            temp.push_back(solution[i]);
        }
    }
    if((int)temp.size())the_solution.push_back(temp);
    return the_solution;
}

std::string format_solution(std::vector<std::string> movements)
{
    std::string formatted;
    for (int i = 0; i < movements.size(); i++)
    {
        if (movements[i].size() > 1)
        {
            if (movements[i][1] == '\'')
            {
                char movement = movements[i][0];
                switch (movement)
                {
                case F_MOVEMENT:
                    formatted.push_back(F_REVERSE_MOVEMENT);
                    break;
                case B_MOVEMENT:
                    formatted.push_back(B_REVERSE_MOVEMENT);
                    break;
                case D_MOVEMENT:
                    formatted.push_back(D_REVERSE_MOVEMENT);
                    break;
                case U_MOVEMENT:
                    formatted.push_back(U_REVERSE_MOVEMENT);
                    break;
                case L_MOVEMENT:
                    formatted.push_back(L_REVERSE_MOVEMENT);
                    break;
                case R_MOVEMENT:
                    formatted.push_back(R_REVERSE_MOVEMENT);
                    break;
                default:
                    break;
                }
            }
            else
            {
                formatted.push_back(movements[i][0]);
                formatted.push_back(movements[i][0]);
            }
        }
        else
        {
            formatted.push_back(movements[i][0]);
        }
    }
    return formatted;
}

std::vector<std::string> string_to_vector(std::string moves)
{
    std::vector<std::string> to_return;
    for (int i = 0; i < moves.size(); i++)
    {
        std::string temp = "";
        temp.push_back(moves[i]);
        switch (moves[i])
        {
        case F_REVERSE_MOVEMENT:
            temp.push_back('\'');
            break;
        case B_REVERSE_MOVEMENT:
            temp.push_back('\'');
            break;
        case D_REVERSE_MOVEMENT:
            temp.push_back('\'');
            break;
        case U_REVERSE_MOVEMENT:
            temp.push_back('\'');
            break;
        case L_REVERSE_MOVEMENT:
            temp.push_back('\'');
            break;
        case R_REVERSE_MOVEMENT:
            temp.push_back('\'');
        default:
            break;
        }
        to_return.push_back(temp);
    }
    return to_return;
}