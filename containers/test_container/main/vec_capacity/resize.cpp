/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:36:33 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/20 12:30:53 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.hpp"

int main()
{
    vector<int> s1;
    s1.push_back(1);
    s1.push_back(2);
    s1.push_back(212121);
    print_vec(s1);//1 2 212121 capacity:4 size:3

    s1.resize(2);
    print_vec(s1);  //1 2 capacity:4 size:2

    // resize
    s1.resize(5);
    print_vec(s1); //1 2 0 0 0 capacity:5 size:5

    s1.resize(8);
    print_vec(s1); //1 2 0 0 0 0 0 0 capacity:10 size:8

    s1.resize(9);
    print_vec(s1); //1 2 0 0 0 0 0 0 0 capacity:10 size:9

    s1.resize(5);
    print_vec(s1); //1 2 0 0 0 capacity:10 size:5

    s1.resize(0);
    print_vec(s1); //1 1 1 1 1 capacity:5 size:5
    vector<int>i (5,1);
    print_vec(i); // 1 1 1 capacity:5 size:3

    i.resize(3,2);
	std::cout << "i.resize(3,2)" << std::endl;
    print_vec(i);

    i.resize(12,2); //1 1 1 2 2 2 2 2 2 2 2 2 capacity:12 size:12
	std::cout << "i.resize(12,2)" << std::endl;
    print_vec(i);
	std::cout << std::endl;
}