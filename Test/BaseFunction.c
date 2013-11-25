//
//  BaseFunction.c
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

int getLength(char *string){
    int i = 0;
    while(string[i] != '\0')
        i++;
    return i;
}