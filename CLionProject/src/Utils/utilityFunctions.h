//
// Created by diego on 25/05/18.
//

#ifndef ROGUEEMBLEMGAME_UTILITYFUNCTIONS_H
#define ROGUEEMBLEMGAME_UTILITYFUNCTIONS_H

#include <iostream>
#include "VirtualKey.h"

namespace utility{
	//Returns a string with a readable value of the VirtualKey enum
	std::string getStringFromVKey(const VirtualKey &vkPressed);

}



#endif //ROGUEEMBLEMGAME_UTILITYFUNCTIONS_H
