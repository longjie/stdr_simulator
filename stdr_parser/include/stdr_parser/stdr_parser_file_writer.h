/******************************************************************************
   STDR Simulator - Simple Two DImensional Robot Simulator
   Copyright (C) 2013 STDR Simulator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
   
   Authors : 
   * Manos Tsardoulias, etsardou@gmail.com
   * Aris Thallas, aris.thallas@gmail.com
   * Chris Zalidis, zalidis@gmail.com 
******************************************************************************/

#ifndef STDR_PARSER_FILE_WRITER
#define STDR_PARSER_FILE_WRITER

#include "stdr_parser/stdr_parser_node.h"

/**
@namespace stdr_parser
@brief The main namespace for STDR parser
**/ 
namespace stdr_parser
{
  /**
  @class FileWriter
  @brief Writes a node tree to a file
  **/ 
  class FileWriter
  {
    private:
     
    public:
    
      /**
      @brief Default constructor
      @return void
      **/
      FileWriter(void);
      
      /**
      @brief Creates an xml from a noise msg
      @param msg [stdr_msgs::Noise] The noise message
      @param file_name [std::string] The file name to write the xml
      @return void
      **/
      void noiseToXml(stdr_msgs::Noise msg,std::string file_name);
  };
}
#endif
