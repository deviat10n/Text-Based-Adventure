#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <ctime>
bool Temp;
bool Lights = false;
bool Unlocked = false;
bool Broken = false;
bool Won = false;
int difficultyHunger;
int difficultySpawn;
int Response;
int CodeA;
int CodeB;
int CodeC;
int CodeD;
int Money = 19;
int Health = 100;
int Hunger = 100;
int Level = 0;
int foodValues[] = { 5,10,20,30,40,50 };
int aidValues[] = { 10,20,30,40 };
int consumableValues[] = { 5,10,20,30,40,50,10,20,30,40 };
std::string foundCodeA = "?";
std::string foundCodeB = "?";
std::string foundCodeC = "?";
std::string foundCodeD = "?";
std::string Name;
std::string examineObject;
std::string Room = "1";
std::string roomCode = "MI001";
std::string itemList[18];
std::string storageList[30];
std::string inventoryList[8];
std::string usedList[30] = { "12", "27" };
std::string foodList[] = { "Crisps (+5%)", "Cookie (+10%)", "Pizza Slice (+20%)", "Sandwich (+30%)", "Pizza (+40%)", "Cake (+50%)" };
std::string foodDesc[] = { "A packet of ready salted crisps.", "A chocolate chip cookie.", "A slice of margherita pizza.", "A cheese & tomato sandwich.", "A full pepperoni pizza.", "An entire chocolate cake. (Jackpot!)" };
std::string aidList[] = { "Plaster (+10%)", "Small Medicine (+20%)", "Bandage (+30%)", "Large Medicine (+40%)" };
std::string aidDesc[] = { "A plaster to aid small wounds.", "A small medicine to restore some health.", "A bandage to aid big wounds.", "A large medicine to restore lots of health." };
std::string consumableList[] = { "Crisps (+5%)", "Cookie (+10%)", "Pizza Slice (+20%)", "Sandwich (+30%)", "Pizza (+40%)", "Cake (+50%)", "Plaster (+10%)", "Small Medicine (+20%)", "Bandage (+30%)", "Large Medicine (+40%)" };
std::string consumableDesc[] = { "A packet of ready salted crisps.", "A chocolate chip cookie.", "A slice of margherita pizza.", "A cheese & tomato sandwich.", "A full pepperoni pizza.", "An entire chocolate cake. (Jackpot!)", "A plaster to aid small wounds.", "A small medicine to restore some health.", "A bandage to aid big wounds.", "A large medicine to restore lots of health." };
std::string miscList[] = { "Axe","Key","Sticks","Scissors","Rope","Material" };
std::string codeList[] = { "Code A", "Code B", "Code C", "Code D" };

void Fight() {
	system("color CF");
	Temp = false;
	std::string enemyList[] = { "Witch", "Ghost", "Spider", "Skeleton", "Vampire", "Gremlin", "Mummy", "Zombie", "Werewolf", "Dragon" };
	int minDamage[] = { 0,5,10,15,20,25,30,35,40,45 };
	int randomNumber = rand() % 10;
	int Damage = rand() % 15;
	Damage = Damage + minDamage[randomNumber];
	std::cout << "\nYou encountered a " << enemyList[randomNumber] << "!\n\n(1)Fight (-" << minDamage[randomNumber] << "~" << ((minDamage[randomNumber]) + 15) << " Health)\n(2)Run (-20 Hunger)\n";
	while (Temp == false) {
		std::cin >> Response;
		if (Response == 1) {
			Temp = true;
			Health = Health - Damage;
			std::cout << "\nYou defeated the " << enemyList[randomNumber] << ", but lost " << Damage << " Health.\n";
		}
		else if (Response == 2) {
			Temp = true;
			Hunger = Hunger - 20;
			std::cout << "You ran away from the " << enemyList[randomNumber] << ", but lost 20 Hunger.\n";
		}
		else std::cout << "Please enter a valid number.\n";
	}
	if (difficultyHunger == 5) {
		Temp = true;
		if (Lights == false) system("color 0A");
		else system("color F2");
	}
	else if (difficultyHunger == 10) {
		Temp = true;
		if (Lights == false) system("color 0E");
		else system("color F6");
	}
	else if (difficultyHunger == 15) {
		Temp = true;
		if (Lights == false) system("color 0C");
		else system("color FC");
	}
}

void examineOptions() {
	std::string Type;
	bool temp2;
	temp2 = false;
	bool temp3 = false;
	int roomNumber;
	for (int i = 0; i < 6; i++) {
		if (foodList[i] == examineObject) {
			Type = "Food";
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (aidList[i] == examineObject) {
			Type = "Aid";
			break;
		}
	}
	if (Type == "Food") std::cout << "\n(1)Take\n(2)Eat\n(3)Cancel\n";
	if (Type == "Aid")  std::cout << "\n(1)Take\n(2)Use\n(3)Cancel\n";
	while (temp2 == false) {
		std::cin >> Response;
		if (Response == 1) {
			for (int i = 0; i < 8; i++) {
				if (inventoryList[i] == "") {
					temp2 = true;
					inventoryList[i] = examineObject;
					temp3 = true;
					if (Room == "C") itemList[(Level + 15)] = "Empty";
					else itemList[((6 * Level) + (std::stoi(Room) - 1))] = "Empty";
					std::cout << "\n" << examineObject << " added to inventory.\n\n";
					break;
				}
			}
			if (temp3 == false) {
				temp2 = true;
				std::cout << "\nError - inventory full\n\n";
			}
		}
		else if (Response == 2) {
			temp2 = true;
			temp3 = false;
			int arrayPosition = 0;
			while (temp3 == false) {
				if (consumableList[arrayPosition] == examineObject) {
					temp3 = true;
				}
				else arrayPosition++;
			}
			if (Type == "Food") {
				Hunger = Hunger + consumableValues[arrayPosition];
				std::cout << "\n" << consumableValues[arrayPosition] << " Hunger restored.\n\n";
			}
			if (Type == "Aid") {
				Health = Health + consumableValues[arrayPosition];
				std::cout << "\n" << consumableValues[arrayPosition] << " Health restored.\n\n";
			}
			if (Room == "C") itemList[(Level + 15)] = "Empty";
			else itemList[((6 * Level) + (std::stoi(Room) - 1))] = "Empty";
			break;
		}
		else if (Response == 3) {
			temp2 = true;
			std::cout << "\n";
		}
		else std::cout << "Please enter a valid number.\n";
	}
}

void Storage() {
	int Addition;
	int roomNumber;
	std::string storageItem;
	std::string charCheck;
	Temp = false;
	bool temp2 = false;
	if (Response == 2) Addition = 0;
	if (Response == 3) Addition = 15;
	roomNumber = std::stoi(Room);
	storageItem = storageList[((5 * Level) + (roomNumber - 1) + Addition)];
	charCheck = storageItem[0];
	if ((charCheck == "0") || (charCheck == "1") || (charCheck == "2") || (charCheck == "3") || (charCheck == "4") || (charCheck == "5") || (charCheck == "6") || (charCheck == "7") || (charCheck == "8") || (charCheck == "9")) {
		std::cout << "\nInside there is " + storageItem + "p.\n\n(1)Take\n(2)Cancel\n";
		while (Temp == false) {
			std::cin >> Response;
			if (Response == 1) {
				Temp = true;
				Money = Money + std::stoi(storageItem);
				storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
				std::cout << "\nPicked up " << storageItem << "p!\n\n";
			}
			else if (Response == 2) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "Please enter a valid number.\n";
		}
	}
	else if (storageItem != "Empty") {
		for (int i = 0; i < 6; i++) {
			if (foodList[i] == storageItem) {
				std::cout << "\nInside there is a " << storageItem << ".\n\n(1)Take\n(2)Eat\n(3)Cancel\n";
				while (Temp == false) {
					std::cin >> Response;
					if (Response == 1) {
						Temp = true;
						for (int i = 0; i < 8; i++) {
							if (inventoryList[i] == "") {
								temp2 = true;
								inventoryList[i] = storageItem;
								storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
								std::cout << "\n" << storageItem << " added to inventory.\n\n";
								break;
							}
						}
						if (temp2 == false) std::cout << "\nError - inventory full\n\n";
					}
					else if (Response == 2) {
						Temp = true;
						Hunger = Hunger + foodValues[i];
						std::cout << "\nThe " << storageItem << " restored " << std::to_string(foodValues[i]) << " Hunger!\n\n";
						storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
					}
					else if (Response == 3) {
						Temp = true;
						std::cout << "\n";
					}
					else std::cout << "Please enter a valid number.\n";
				}
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (aidList[i] == storageItem) {
				std::cout << "\nInside there is a " << storageItem << ".\n\n(1)Take\n(2)Use\n(3)Cancel\n";
				while (Temp == false) {
					std::cin >> Response;
					if (Response == 1) {
						Temp = true;
						for (int i = 0; i < 8; i++) {
							if (inventoryList[i] == "") {
								temp2 = true;
								inventoryList[i] = storageItem;
								storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
								std::cout << "\n" << storageItem << " added to inventory.\n\n";
								break;
							}
						}
						if (temp2 == false) std::cout << "\nError - inventory full\n\n";
					}
					else if (Response == 2) {
						Temp = true;
						Health = Health + aidValues[i];
						std::cout << "\nThe " << storageItem << " restored " << std::to_string(aidValues[i]) << " Health!\n\n";
						storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
					}
					else if (Response == 3) {
						Temp = true;
						std::cout << "\n";
					}
					else std::cout << "Please enter a valid number.\n";
				}
				break;
			}
		}
		for (int i = 0; i < 6; i++) {
			if (miscList[i] == storageItem) {
				std::cout << "\nInside there is a " << storageItem << ".\n\n(1)Take\n(2)Cancel\n";
				while (Temp == false) {
					std::cin >> Response;
					if (Response == 1) {
						Temp = true;
						for (int i = 0; i < 8; i++) {
							if (inventoryList[i] == "") {
								temp2 = true;
								inventoryList[i] = storageItem;
								storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
								std::cout << "\n" << storageItem << " added to inventory.\n\n";
								break;
							}
						}
						if (temp2 == false) std::cout << "\nError - inventory full\n\n";
					}
					else if (Response == 2) {
						Temp = true;
						std::cout << "\n";
					}
					else std::cout << "Please enter a valid number.\n";
				}
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (codeList[i] == storageItem) {
				std::cout << "\n" << storageItem << " - One of the 4 parts of the code needed to escape out of the main entrance!.\n\n(1)Take\n(2)Cancel\n";
				while (Temp == false) {
					std::cin >> Response;
					if (Response == 1) {
						Temp = true;
						if (storageItem == "Code A") foundCodeA = std::to_string(CodeA);
						else if (storageItem == "Code B") foundCodeB = std::to_string(CodeB);
						else if (storageItem == "Code C") foundCodeC = std::to_string(CodeC);
						else if (storageItem == "Code D") foundCodeD = std::to_string(CodeD);
						std::cout << "\n" << storageItem << " added to code.\n\n";
						storageList[((5 * Level) + (roomNumber - 1) + Addition)] = "Empty";
					}
					else if (Response == 2) {
						Temp = true;
						std::cout << "\n";
					}
					else std::cout << "Please enter a valid number.\n";
				}
				break;
			}
		}
	}
	else {
		std::cout << "\nIt is empty.\n\n";
		Temp = true;
	}
}

void vendingMachine() {
	system("color 5F");
	Temp = false;
	bool temp2 = false;
	int foodPrices[] = { 25,50,70,90,110,130 };
	int aidPrices[] = { 50,70,90,110 };
	if (Response == 2) {
		std::cout << "\nThe vending machine is working now the power has been restored!\n\n(1)Crisps - 25p\n(2)Cookie - 50p\n(3)Pizza Slice - 70p\n(4)Sandwich - 90p\n(5)Pizza - 110p\n(6)Cake - 130p\n(7)Cancel\n";
		while (Temp == false) {
			std::cin >> Response;
			if ((Response == 1) || (Response == 2) || (Response == 3) || (Response == 4) || (Response == 5) || (Response == 6)) {
				Temp = true;
				if ((Money - foodPrices[(Response - 1)]) < 0) std::cout << "\nYou can't afford this item.\n";
				else {
					for (int i = 0; i < 8; i++) {
						if (inventoryList[i] == "") {
							temp2 = true;
							inventoryList[i] = foodList[(Response - 1)];
							std::cout << "\nPurchase successful. " << foodList[(Response - 1)] << " added to inventory.\n\n";
							Money = Money - foodPrices[(Response - 1)];
							break;
						}
					}
					if (temp2 == false) std::cout << "\nError - inventory full\n\n";
				}
			}
			else if (Response == 7) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "Please enter a valid number.\n";
		}
	}
	else if (Response == 3) {
		std::cout << "\nThe vending machine is working now the power has been restored!\n\n(1)Plaster - 50p\n(2)Small Medicine - 70p\n(3)Bandage - 90p\n(4)Large Medicine - 110p\n(5)Cancel\n";
		while (Temp == false) {
			std::cin >> Response;
			if ((Response == 1) || (Response == 2) || (Response == 3) || (Response == 4)) {
				Temp = true;
				if ((Money - aidPrices[(Response - 1)]) < 0) std::cout << "\nYou can't afford this item.\n";
				else {
					for (int i = 0; i < 8; i++) {
						if (inventoryList[i] == "") {
							temp2 = true;
							inventoryList[i] = aidList[(Response - 1)];
							std::cout << "\nPurchase successful. " << aidList[(Response - 1)] << " added to inventory.\n\n";
							Money = Money - aidPrices[(Response - 1)];
							break;
						}
					}
					if (temp2 == false) std::cout << "\nError - inventory full\n\n";
				}
			}
			else if (Response == 7) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "Please enter a valid number.\n";
		}
	}
	if (difficultyHunger == 5) {
		Temp = true;
		if (Lights == false) system("color 0A");
		else system("color F2");
	}
	else if (difficultyHunger == 10) {
		Temp = true;
		if (Lights == false) system("color 0E");
		else system("color F6");
	}
	else if (difficultyHunger == 15) {
		Temp = true;
		if (Lights == false) system("color 0C");
		else system("color FC");
	}
}

void Examine()
{
	int arrayPosition = 0;
	Temp = false;
	std::string Item;
	std::string itemName;
	std::string roomName[] = { "MI001", "MI002", "MI003" , "MI004" , "MI005","MI101", "MI102", "MI103" , "MI104" , "MI105","MI201", "MI202", "MI203" , "MI204" , "MI205", "Corridor (Floor 0)", "Corridor (Floor 1)", "Corridor (Floor 2)" };
	std::string storage1[] = { "Cupboard", "Bag", "Filing Cabinet", "Under Desk", "Drawers", "Cupboard", "Bag", "Filing Cabinet", "Under Desk", "Drawers","Cupboard", "Bag", "Cupboard", "Under Desk", "Drawers", "Vending Machine (Food)","Vending Machine (Food)", "Vending Machine (Food)" };
	std::string storage2[] = { "Drawers", "Under Desk", "Cupboard", "Bag", "Filing Cabinet", "Drawers", "Under Desk", "Cupboard", "Bag", "Filing Cabinet", "Drawers", "Under Desk", "Filing Cabinet", "Bag", "Filing Cabinet", "Vending Machine (Aid)", "Vending Machine (Aid)", "Vending Machine (Aid)" };
	while (Temp == false) {
		if (roomName[arrayPosition] == roomCode) {
			Temp = true;
		}
		else arrayPosition++;
	}
	if (Room != "C") Item = itemList[((6 * Level) + (std::stoi(Room) - 1))];
	else Item = itemList[Level + 15];
	if (Item == "Empty") {
		itemName = "Empty";
	}
	else {
		itemName = consumableList[std::stoi(Item)];
	}
	if (roomCode == "MI203") {
		std::cout << "\n(1)Lever\n(2)" << storage1[arrayPosition] << "\n(3)" << storage2[arrayPosition] << "\n(4)Cancel\n";
		Temp = false;
		while (Temp == false) {
			std::cin >> Response;
			if (Response == 1) {
				Temp = true;
				if (Lights == false) {
					Lights = true;
					std::cout << "\nThe lever seemed to turn the power back on!\n\n";
					if (difficultyHunger == 5) {
						Temp = true;
						system("color F2");
					}
					else if (difficultyHunger == 10) {
						Temp = true;
						system("color F6");
					}
					else if (difficultyHunger == 15) {
						Temp = true;
						system("color FC");
					}
				}
				else std::cout << "\nThe lever is already switched on.\n\n";
			}
			else if ((Response == 2) || (Response == 3)) {
				Temp = true;
				if (Room == "C") {
					if (Lights == true) {
						vendingMachine();
					}
					else {
						std::cout << "\nThe vending machines are out of order whilst the power is off.\n\n";
					}
				}
				else {
					Storage();
				}
			}
			else if (Response == 4) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "\nPlease enter a valid number.\n";
		}
	}
	else {
		std::cout << "\n(1)" << itemName << "\n(2)" << storage1[arrayPosition] << "\n(3)" << storage2[arrayPosition] << "\n(4)Cancel\n";
		Temp = false;
		while (Temp == false) {
			std::cin >> Response;
			if (Response == 1) {
				if (itemName == "Empty") {
					std::cout << "\nThere is nothing to examine.\n";
					Temp = true;
					Examine();
				}
				else {
					Temp = true;
					std::cout << "\n" << consumableDesc[std::stoi(Item)] << "\n";
					examineObject = itemName;
					examineOptions();
				}
			}
			else if ((Response == 2) || (Response == 3)) {
				Temp = true;
				if (Room == "C") {
					if (Lights == true) {
						vendingMachine();
					}
					else {
						std::cout << "\nThe vending machines are out of order whilst the power is off.\n\n";
					}
				}
				else {
					Storage();
				}
			}
			else if (Response == 4) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "\nPlease enter a valid number.\n";
		}
	}
}

void Inventory()
{
	Temp = false;
	bool temp2 = false;
	bool rope = false;
	bool scissors = false;
	bool material = false;
	bool sticks = false;
	bool craftable = false;
	int sticksPosition;
	int ropePosition;
	int scissorsPosition;
	int materialPosition;
	int response2;
	auto arrayEnd = std::remove(std::begin(inventoryList), std::end(inventoryList), "");
	std::cout << "\n(1) " << inventoryList[0] << "\n(2) " << inventoryList[1] << "\n(3) " << inventoryList[2] << "\n(4) " << inventoryList[3] << "\n(5) " << inventoryList[4] << "\n(6) " << inventoryList[5] << "\n(7) " << inventoryList[6] << "\n(8) " << inventoryList[7] << "\n(9)Cancel\n";
	while (Temp == false) {
		std::cin >> Response;
		if ((Response == 1) || (Response == 2) || (Response == 3) || (Response == 4) || (Response == 5) || (Response == 6) || (Response == 7) || (Response == 8)) {
			Temp = true;
			if (inventoryList[(Response - 1)] == "") std::cout << "\nThere is nothing to interact with.\n\n";
			else if (inventoryList[(Response - 1)] == "Hand Glider") std::cout << "\nI wonder where a handglider could be useful...\n\n";
			else {
				for (int i = 0; i < 6; i++) {
					if (foodList[i] == inventoryList[(Response - 1)]) {
						std::cout << "\n" << foodList[i] << "\n" << foodDesc[i] << "\n\n(1)Eat\n(2)Cancel\n";
						while (temp2 == false) {
							std::cin >> response2;
							if (response2 == 1) {
								temp2 = true;
								Hunger = Hunger + foodValues[i];
								std::cout << "\n" << foodList[i] << " restored " << foodValues[i] << " Hunger.\n\n";
								inventoryList[(Response - 1)] = "";
							}
							else if (response2 == 2) {
								temp2 = true;
								std::cout << "\n";
							}
							else {
								std::cout << "Please enter a valid response.\n";
							}
						}
						break;
					}
				}
				for (int i = 0; i < 4; i++) {
					if (aidList[i] == inventoryList[(Response - 1)]) {
						std::cout << "\n" << aidList[i] << "\n" << aidDesc[i] << "\n\n(1)Use\n(2)Cancel\n";
						while (temp2 == false) {
							std::cin >> response2;
							if (response2 == 1) {
								temp2 = true;
								Health = Health + aidValues[i];
								std::cout << "\n" << aidList[i] << " restored " << aidValues[i] << " Health.\n\n";
								inventoryList[(Response - 1)] = "";
							}
							else if (response2 == 2) {
								temp2 = true;
								std::cout << "\n";
							}
							else std::cout << "Please enter a valid response.\n";
						}
						break;
					}
				}
				for (int i = 0; i < 6; i++) {
					if (miscList[i] == inventoryList[(Response - 1)]) {
						if (miscList[i] == "Key") std::cout << "\nThere must be a locked door somewhere...\n\n";
						else if (miscList[i] == "Axe") std::cout << "\nThere must be a use for an axe somewhere...\n\n";
						else craftable = true;
					}
				}
				if (craftable == true) {
					for (int i = 0; i < 8; i++) {
						if (inventoryList[i] == "Sticks") {
							sticks = true;
							sticksPosition = i;
						}
						if (inventoryList[i] == "Rope") {
							rope = true;
							ropePosition = i;
						}
						if (inventoryList[i] == "Material") {
							material = true;
							materialPosition = i;
						}
						if (inventoryList[i] == "Scissors") {
							scissors = true;
							scissorsPosition = i;
						}
					}
					std::cout << scissors << sticks << material << rope;
					if ((scissors == true) && (sticks == true) && (material == true) && (rope == true)) {
						std::cout << "\nYou have all the components to craft a hand glider!\n\n(1)Craft\n(2)Cancel\n";
						temp2 = false;
						while (temp2 == false) {
							std::cin >> Response;
							if (Response == 1) {
								temp2 = true;
								inventoryList[scissorsPosition] = "";
								inventoryList[ropePosition] = "";
								inventoryList[materialPosition] = "";
								inventoryList[sticksPosition] = "";
								for (int i = 0; i < 8; i++) {
									if (inventoryList[i] == "") {
										inventoryList[i] = "Hand Glider";
										std::cout << "\nHand Glider added to inventory.\n\n";
										break;
									}
								}
							}
							else if (Response == 2) {
								temp2 = true;
								std::cout << "\n";
							}
							else std::cout << "Please enter a valid number.\n";
						}
					}
					else {
						std::cout << "\nIt looks as though you can make something, but you don't have enough parts yet...\n\n";
					}
				}
			}
		}
		else if (Response == 9) {
			Temp = true;
			std::cout << "\n";
		}
		else std::cout << "Please enter a valid number.\n";
	}
}

void Move()
{
	int levelTemp = Level;
	int passcode = ((1000 * CodeA) + (100 * CodeB) + (10 * CodeC) + CodeD);
	std::string lOffDesc[] = { "The room is dark and full of computers. There is a cupboard up against the wall and a set of drawers in the front desk.","The room is dark and there are endless rows of desks, all facing a whiteboard at the front. There is a bag that has been left on one of the desks.","The room is dark and fairly empty, this must have been a spare classroom. There is just a cupboard and a filing cabinet up against the wall. ","The room is dark and all of the surfaces feel dusty, this room hasn't been used in a long time. There is a set of drawers in the front desk, and a bag sitting on top of it.","The room is dark and there are lots of trailing cables on the floor, I have to be careful not to trip up. There is a bag in the corner of the room, and a filing cabinet on the opposite side.","The room is dark and all of the surfaces feel dusty, this room hasn't been used in a long time. There is a set of drawers in the front desk, and a bag sitting on top of it.","The room is dark and there are lots of trailing cables on the floor, I have to be careful not to trip up. There is a bag in the corner of the room, and a filing cabinet on the opposite side.","The room is dark and full of computers. There is a cupboard up against the wall and a set of drawers in the front desk.","The room is dark and there are endless rows of desks, all facing a whiteboard at the front. There is a bag that has been left on one of the desks.","The room is dark and fairly empty, this must have been a spare classroom. There is just a cupboard and a filing cabinet up against the wall. ","The room is dark and there are endless rows of desks, all facing a whiteboard at the front. There is a bag that has been left on one of the desks.","The room is dark and fairly empty, this must have been a spare classroom. There is just a cupboard and a filing cabinet up against the wall. ","There is a lever in the middle of this room and a lot of panels on the walls which all appear to be off. There is a filing cabinet and a cupboard by the door.","The room is dark and there are lots of trailing cables on the floor, I have to be careful not to trip up. There is a bag in the corner of the room, and a filing cabinet on the opposite side.","The room is dark and full of computers. There is a cupboard up against the wall and a set of drawers in the front desk.", "A big empty hallway with a mass of doors leading into classrooms, and stairs leading up to the first floor.","A big empty hallway with a mass of doors leading into classrooms, and stairs leading down to the ground floor and up to the second floor.","A big empty hallway with a mass of doors leading into classrooms, and stairs leading down to the first floor." };
	std::string lOnDesc[] = { "The artificial lights are blinding despite it being pitch black outside. There is a cupboard up against the wall and a set of drawers in the front desk.","The bright lights are reflecting off the whiteboard making the whole room seem to glow. There is a bag that has been left on one of the desks, and space under the front desk.", "Having the lights on makes this room seem even bigger and emptier. There is just a cupboard and a filing cabinet up against the wall. ", "With the lights on, this room is even worse than I first thought, it is covered in cobwebs. There is a set of drawers in the front desk, and a bag sitting on top of it.", "Navigating this mess of wires is a lot easier with the lights on, although I'm not sure what they all do. There is a bag in the corner of the room, and a filing cabinet on the opposite side.", "With the lights on, this room is even worse than I first thought, it is covered in cobwebs. There is a set of drawers in the front desk, and a bag sitting on top of it.", "Navigating this mess of wires is a lot easier with the lights on, although I'm not sure what they all do. There is a bag in the corner of the room, and a filing cabinet on the opposite side.", "The artificial lights are blinding despite it being pitch black outside. There is a cupboard up against the wall and a set of drawers in the front desk.", "The bright lights are reflecting off the whiteboard making the whole room seem to glow. There is a bag that has been left on one of the desks, and space under the front desk.", "Having the lights on makes this room seem even bigger and emptier. There is just a cupboard and a filing cabinet up against the wall. ", "The bright lights are reflecting off the whiteboard making the whole room seem to glow. There is a bag that has been left on one of the desks, and space under the front desk.", "Having the lights on makes this room seem even bigger and emptier. There is just a cupboard and a filing cabinet up against the wall. ", "There is a lever in the middle of this room and all of the panels which were off have all filled with bright LED's. There is a filing cabinet and a cupboard by the door.", "Navigating this mess of wires is a lot easier with the lights on, although I'm not sure what they all do. There is a bag in the corner of the room, and a filing cabinet on the opposite side.", "The artificial lights are blinding despite it being pitch black outside. There is a cupboard up against the wall and a set of drawers in the front desk.", "A big empty hallway with a mass of doors leading into classrooms, and stairs leading up to the first floor.","A big empty hallway with a mass of doors leading into classrooms, and stairs leading down to the ground floor and up to the second floor.","A big empty hallway with a mass of doors leading into classrooms, and stairs leading down to the first floor." };
	Temp = false;
	bool temp2 = false;
	int randomNumber = rand() % 100;
	if ((Room == "1") || (Room == "2") || (Room == "3") || (Room == "4") || (Room == "5")) {
		std::cout << "\n(1)Corridor (Floor " << Level << ")\n(2)Cancel\n";
		while (Temp == false) {
			std::cin >> Response;
			if (Response == 1) {
				Temp = true;
				Hunger = Hunger - difficultyHunger;
				Room = "C";
				roomCode = "Corridor (Floor " + std::to_string(Level) + ")";
				if (randomNumber < difficultySpawn) {
					Fight();
				}
				if (Lights == false) {
					std::cout << "\n" << lOffDesc[(15 + Level)] << "\n\n";
				}
				else std::cout << "\n" << lOnDesc[(15 + Level)] << "\n\n";
			}
			else if (Response == 2) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "\nPlease enter a valid number.\n";
		}
	}
	else {
		if (Level == 0) std::cout << "\n(1)MI" << Level << "01\n(2)MI" << Level << "02\n(3)MI" << Level << "03\n(4)MI" << Level << "04\n(5)MI" << Level << "05\n(6)Stairs to Floor 1\n(7)Main Entrance\n(8)Cancel\n";
		else if (Level == 1) std::cout << "\n(1)MI" << Level << "01\n(2)MI" << Level << "02\n(3)MI" << Level << "03\n(4)MI" << Level << "04\n(5)MI" << Level << "05\n(6)Stairs to Floor 0\n(7)Stairs to Floor 2\n(8)Cancel\n";
		else if (Level == 2) std::cout << "\n(1)MI" << Level << "01\n(2)MI" << Level << "02\n(3)MI" << Level << "03\n(4)MI" << Level << "04\n(5)MI" << Level << "05\n(6)Stairs to Floor 1\n(7)Ladder to Roof\n(8)Cancel\n";
		while (Temp == false) {
			std::cin >> Response;
			if ((Level == 2) && (Response == 3)) {
				Temp = true;
				if (Unlocked == false) {
					std::cout << "\nThis door appears to be locked.\n\n(1)Unlock\n(2)Cancel\n";
					while (temp2 == false) {
						std::cin >> Response;
						if (Response == 1) {
							temp2 = true;
							for (int i = 0; i < 8; i++) {
								if (inventoryList[i] == "Key") {
									Unlocked = true;
									inventoryList[i] = "";
									std::cout << "\nRoom unlocked!\n\n";
									Hunger = Hunger - difficultyHunger;
									Room = "3";
									roomCode = "MI203";
									if (randomNumber < difficultySpawn) {
										Fight();
									}
									if (Lights == false) {
										std::cout << "\n" << lOffDesc[((Level * 5) + (std::stoi(Room) - 1))] << "\n\n";
									}
									else std::cout << "\n" << lOnDesc[((Level * 5) + (std::stoi(Room) - 1))] << "\n\n";
									break;
								}
							}
							if (Unlocked == false) {
								std::cout << "\nIt looks like we might need to find a key first...\n\n";
							}
						}
						else if (Response == 2) {
							temp2 = true;
							std::cout << "\n";
						}
						else std::cout << "Please enter a valid number.";
					}
				}
				else {
					Hunger = Hunger - difficultyHunger;
					Room = "3";
					roomCode = "MI203";
					if (randomNumber < difficultySpawn) {
						Fight();
					}
					if (Lights == false) {
						std::cout << "\n" << lOffDesc[((Level * 5) + (std::stoi(Room) - 1))] << "\n\n";
					}
					else std::cout << "\n" << lOnDesc[((Level * 5) + (std::stoi(Room) - 1))] << "\n\n";
				}
			}
			else if ((Response == 1) || (Response == 2) || (Response == 3) || (Response == 4) || (Response == 5)) {
				Temp = true;
				Hunger = Hunger - difficultyHunger;
				Room = std::to_string(Response);
				roomCode = "MI" + std::to_string(Level) + "0" + Room;
				if (randomNumber < difficultySpawn) {
					Fight();
				}
				if (Lights == false) {
					std::cout << "\n" << lOffDesc[((Level * 5) + (std::stoi(Room) - 1))] << "\n\n";
				}
				else std::cout << "\n" << lOnDesc[((Level * 5) + (std::stoi(Room) - 1))] << "\n\n";
			}
			else if (((Level == 0) && (Response == 6)) || ((Level == 1) && (Response == 7))) {
				Temp = true;
				Hunger = Hunger - difficultyHunger;
				if (levelTemp == 0) Level = 1;
				if (levelTemp == 1) Level = 2;
				Room = "C";
				roomCode = "Corridor (Floor " + std::to_string(Level) + ")";
				if (randomNumber < difficultySpawn) {
					Fight();
				}
				if (Lights == false) {
					std::cout << "\n" << lOffDesc[(15 + Level)] << "\n\n";
				}
				else std::cout << "\n" << lOnDesc[(15 + Level)] << "\n\n";
			}
			else if (((Level == 1) || (Level == 2)) && (Response == 6)) {
				Temp = true;
				Hunger = Hunger - difficultyHunger;
				if (levelTemp == 2) Level = 1;
				if (levelTemp == 1) Level = 0;
				Room = "C";
				roomCode = "Corridor (Floor " + std::to_string(Level) + ")";
				if (randomNumber < difficultySpawn) {
					Fight();
				}
				if (Lights == false) {
					std::cout << "\n" << lOffDesc[(15 + Level)] << "\n\n";
				}
				else std::cout << "\n" << lOnDesc[(15 + Level)] << "\n\n";
			}
			else if ((Level == 0) && (Response == 7)) {
				Temp = true;
				if (Lights == false) {
					std::cout << "\nThe front door of the building, locked shut. There is a keypad which appears to be non functional at the moment. I wonder if there is a way to get the power back on...\n\n";
				}
				else {
					Temp = false;
					std::cout << "\nThe front door of the building, locked shut. There is a keypad which is lit up. Operate keypad?\n\n(1)Use Keypad\n(2)Cancel\n";
					while (Temp == false) {
						std::cin >> Response;
						if (Response == 1) {
							Temp = true;
							temp2 = false;
							std::cout << "\nEnter Passcode:\n";
							std::cin >> Response;
							if (Response == passcode) {
								Won = true;
								std::cout << "\n\nA green light appears, and the front door swings open. You run outside and inhale the cool fresh air. You had made it out alive.\n\n";
							}
							else std::cout << "\nThe passcode is incorrect.\n\n";
						}
						else if (Response == 2) {
							Temp = true;
							std::cout << "\n";
						}
						else std::cout << "Please enter a valid number.";
					}
				}
			}
			else if ((Level == 2) && (Response == 7)) {
				Temp = true;
				temp2 = false;
				if (Broken == false) {
					std::cout << "\nYou ascend the ladder, at the top of which is a door that is boarded shut. You will need an axe to break this down.\n\n(1)Use Axe\n(2)Cancel\n";
					while (temp2 == false) {
						std::cin >> Response;
						if (Response == 1) {
							temp2 = true;
							for (int i = 0; i < 8; i++) {
								if (inventoryList[i] == "Axe") {
									Broken = true;
									inventoryList[i] = "";
									std::cout << "\nYou managed to break through!\n\n";
									break;
								}
							}
						}
						else if (Response == 2) {
							temp2 = true;
							std::cout << "\n";
						}
						else std::cout << "Please enter a valid number.\n";
					}
				}
				if (Broken == true) {
					temp2 = false;
					std::cout << "\nYou made it out onto the roof, but you haven't escaped yet, there is no way down other than to jump, but it looks too high to attempt without proper equipment.\n\n(1)Jump\n(2)Cancel\n";
					while (temp2 == false) {
						std::cin >> Response;
						if (Response == 1) {
							temp2 = true;
							for (int i = 0; i < 8; i++) {
								if (inventoryList[i] == "Hand Glider") {
									Won = true;
									inventoryList[i] = "";
									std::cout << "\nYou jumped off the roof using your hand glider, and swooped safely down to the ground without harm. You have escaped!\n\n";
									break;
								}
							}
							if (Won == false) {
								std::cout << "\nYou jumped off the roof of the building, but it was too high for you to survive the landing.\n\n";
								Health = 0;
							}
						}
						else if (Response == 2) {
							temp2 = true;
							std::cout << "\n";
						}
						else std::cout << "Please enter a valid number.";
					}
				}
			}
			else if (Response == 8) {
				Temp = true;
				std::cout << "\n";
			}
			else std::cout << "Please enter a valid number.\n";
		}
	}
}

void Hud()
{
	while ((Health > 0) && (Hunger > 0) && (Won == false)) {
		Temp = false;
		if (Health > 100) Health = 100;
		if (Hunger > 100) Hunger = 100;
		if ((foundCodeA == "?") && (foundCodeB == "?") && (foundCodeC == "?") && (foundCodeD == "?")) {
			std::cout << "Health: " << std::to_string(Health) << "%\nHunger: " << std::to_string(Hunger) << "%\nMoney: " << Money << "p\nRoom: " << roomCode << "\n\n(1)Examine\n(2)Inventory\n(3)Move\n";
		}
		else std::cout << "Code: " << foundCodeA << " " << foundCodeB << " " << foundCodeC << " " << foundCodeD << "\nHealth: " << std::to_string(Health) << "%\nHunger: " << std::to_string(Hunger) << "%\nMoney: " << Money << "p\nRoom: " << roomCode << "\n\n(1)Examine\n(2)Inventory\n(3)Move\n";
		while (Temp == false) {
			std::cin >> Response;
			if (Response == 1) {
				Temp = true;
				Examine();
			}
			else if (Response == 2) {
				Temp = true;
				Inventory();
			}
			else if (Response == 3) {
				Temp = true;
				Move();
			}
			else std::cout << "Please enter a valid number.\n";
		}
	}
}

void addToList(std::string itemName)
{
	Temp = false;
	bool temp2;
	int randomNumber;
	while (Temp == false) {
		temp2 = false;
		randomNumber = rand() % 30;
		for (int i = 0; i < 30; i++) {
			if (usedList[i] == std::to_string(randomNumber)) {
				temp2 = true;
				break;
			}
		}
		if (temp2 == true) Temp = false;
		else {
			Temp = true;
			storageList[randomNumber] = itemName;
			for (int i = 0; i < 30; i++) {
				if (usedList[i] == "") {
					usedList[i] = std::to_string(randomNumber);
					break;
				}
			}
		}
	}
}

void main()
{
	system("color 0B");
	int i = 0;
	int randomNumber;
	std::string Result;
	srand(time(0));
	CodeA = rand() % 10;
	CodeB = rand() % 10;
	CodeC = rand() % 10;
	CodeD = rand() % 10;
	while (i < (sizeof(itemList) / sizeof(*itemList))) {
		randomNumber = rand() % 10;
		itemList[i] = std::to_string(randomNumber);
		i++;
	}
	i = 0;
	while (i < (sizeof(storageList) / sizeof(*storageList))) {
		randomNumber = rand() % 3;
		if (randomNumber == 0) Result = "Empty";
		if (randomNumber == 1) {
			randomNumber = ((rand() % 99) + 1);
			Result = std::to_string(randomNumber);
		}
		if (randomNumber == 2) {
			randomNumber = (rand() % 10);
			Result = consumableList[randomNumber];
		}
		storageList[i] = Result;
		i++;
	}
	addToList("Axe");
	addToList("Key");
	addToList("Code A");
	addToList("Code B");
	addToList("Code C");
	addToList("Code D");
	addToList("Sticks");
	addToList("Scissors");
	addToList("Rope");
	addToList("Material");
	std::cout << "MI:MI\nMission Impossible: MI Building Escape\n\n(1)Start\n(2)Instructions\n";
	Temp = false;
	while (Temp == false) {
		std::cin >> Response;
		if (Response == 2) {
			std::cout << "Welcome to MI:MI. The aim is to escape the MI building by exploring and solving puzzles before you die from injuries or starvation.\n\nYou play by entering the numbers next to the commands you choose. You lose a certain amount of hunger, depending on what difficulty setting you choose, every time you move between rooms, so be diligent in your exploration to find food as well as the exit. Best of luck!\n";
			Temp = true;
		}
		else if (Response == 1) {
			Temp = true;
		}
		else std::cout << "Please enter a valid number.\n";
	}
	std::cout << "\nSelect your difficulty level:\n\n(1)Easy\n(2)Normal\n(3)Hard\n";
	Temp = false;
	while (Temp == false) {
		std::cin >> Response;
		if (Response == 1) {
			Temp = true;
			system("color 0A");
		}
		else if (Response == 2) {
			Temp = true;
			system("color 0E");
		}
		else if (Response == 3) {
			Temp = true;
			system("color 0C");
		}
		else std::cout << "Please enter a valid number.\n";
	}
	difficultyHunger = (Response * 5);
	difficultySpawn = ((Response + 1) * 10);
	std::cout << "\nPlease enter your name:\n";
	std::cin >> Name;
	std::cout << "\nYou wake up in a dark room, surrounded by computers. All of your belongings are missing, except for 19p in loose change in your left pocket.\n\n";
	Hud();
	if (Won == true) {
		system("color A1");
		std::cout << " __   __ ___   _   _  __        __ ___  _   _ " << std::endl << " \\ \\ / // _ \\ | | | | \\ \\      / /|_ _|| \\ | |" << std::endl << "  \\ V /| | | || | | |  \\ \\ /\\ / /  | | |  \\| |" << std::endl << "   | | | |_| || |_| |   \\ V  V /   | | | |\\  |" << std::endl << "   |_|  \\___/  \\___/     \\_/\\_/   |___||_| \\_|" << std::endl;
		std::cout << "\nCongratulations " << Name << ", you successfully beat the game! There is another way to win though, so try and find that next time!\n\nPlease press enter to quit.\n";
		std::cin.ignore(std::cin.rdbuf()->in_avail() + 1);
		return;
	}
	else {
		system("color C0");
		std::cout << " __   __ ___   _   _   _      ___   ____   _____ " << std::endl << " \\ \\ / // _ \\ | | | | | |    / _ \\ / ___| | ____|" << std::endl << "  \\ V /| | | || | | | | |   | | | |\\___ \\ |  _|  " << std::endl << "   | | | |_| || |_| | | |___| |_| | ___) || |___ " << std::endl << "   |_|  \\___/  \\___/  |_____|\\___/ |____/ |_____|" << std::endl;
		std::cout << "\nCommiserations " << Name << ", you unfortunately didn't beat the game. There is another way to win though, so maybe try that way next time!\n\nPlease press enter to quit.\n";
		std::cin.ignore(std::cin.rdbuf()->in_avail() + 1);
		return;
	}
} 