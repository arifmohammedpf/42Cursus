/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:33:40 by arimoham          #+#    #+#             */
/*   Updated: 2025/07/01 14:44:56 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main(void)
{
	PhoneBook phoneBook;
	std::string input;
	Contact contact;

	while (1)
	{
		std::cout << "--COMMANDS--" << std::endl;
		std::cout << "ADD" << std::endl;
		std::cout << "SEARCH" << std::endl;
		std::cout << "EXIT" << std::endl;
		std::cout << "----" << std::endl;
		std::cout << "Enter a Command: ";
		if (!std::getline(std::cin, input))
			break;
		if (input == "EXIT")
			break;
		else if (input == "ADD")
		{
			contact.setFirstName();
			contact.setLastName();
			contact.setNickname();
			contact.setPhoneNumber();
			contact.setDarkestSecret();
			phoneBook.addContact(contact);
		}
		else if (input == "SEARCH")
			phoneBook.searchContact();
	}
	return (0);
}
