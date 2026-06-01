/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:33:17 by arimoham          #+#    #+#             */
/*   Updated: 2025/07/01 14:30:56 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook
{
private:
	Contact _contacts[8];
	int _index;
	int _maxIndex;

public:
	PhoneBook(void);
	~PhoneBook(void);
	void addContact(Contact contact);
	void searchContact(void);
	void printContacts(void);
};

#endif
