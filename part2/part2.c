#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "register.h"
#include <stdio.h>

#define BOOT_PIN 21
#define MaxLen 8


char line[MaxLen + 1];
void ReadLine(void){
    uint idx = 0;
    while(1){
        char c = getchar_timeout_us(200);
        
        //enter
        if (c == 0x0D){
            //line[idx] = 0;
            //Convert the str to Hex int
            return;
        }
        
        //only characters
        if ((c >= 0x20) && (c <= 0x7E)){
            printf("%c", c);
            if (idx < MaxLen){
                line[idx++] = c;
            }
        }
    }
}


int main() {
    ADDRESS user_input;
    ADDRESS user_input1;
    ADDRESS user_input2;
    ADDRESS user_input3;
    stdio_init_all();
    while(stdio_usb_connected()!=true);
    gpio_init(BOOT_PIN);
    gpio_set_dir(BOOT_PIN, GPIO_IN);
    
    //testing the input function
    /*
    while(1){
        printf("\nEnter Line:");
        n = ReadLine();
        printf("\nYou typed: %x", n);
    }
    
    */
    printf("Press BOOT PIN to Write Value to Address\n");
    
    while(1){
        printf("\nRead Mode, Please Enter a Valid Adddress");
        printf("\nInput: \t");
        ReadLine();
        user_input = (long int)strtoul(line, NULL, 16);
        printf("\nThe address is %x", user_input);
        ADDRESS results = register_read(user_input);
        printf("\nThe Value of this address is ");
        printf("%x\n", results);
        printf("\n================================");
        if (gpio_get(BOOT_PIN) == 0)
            break;
    }
    
    while(1){
        printf("\nWRITE Mode, Please Enter a Valid Adddress");
        printf("\nInput: \t");
        ReadLine();
        user_input1 = (long int)strtoul(line, NULL, 16);
        printf("\nThe address is %x", user_input1);
        ADDRESS results = register_read(user_input1);
        printf("\nThe Value of this address is ");
        printf("%x\n", results);
        printf("\n###################################\n");
        printf("\n$$$$$$$$$$$$START_WRITE$$$$$$$$$$$$\n");
        
        printf("\nPlease enter a value you want to write in this address \ninput value: \t");
        ReadLine();
        user_input2 = (long int)strtoul(line, NULL, 16);
        register_write(user_input1, user_input2);
        ADDRESS results1 = register_read(user_input1);
        printf("\nAfter Writing: %x", results1);
        printf("\n>>>>>>>>>>>>MASK>>>>>>>>>>>>>>>>>>\n ");
        
        printf("\nPlease enter a MASK \nInput Value: \t");
        ReadLine();
        user_input3 = (long int)strtoul(line, NULL, 16);
        uint32_t results2 = (uint32_t)results1 & (uint32_t)user_input3;
        printf("\nAfter Musking: %x", results2);
        printf("\n>>>>>>>>>>>>DONE>>>>>>>>>>>>>>>>>> ");
        
        sleep_ms(1000);
    }
    return 0;
}