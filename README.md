# Lab2b_Part2 Yuchen Wang Worked With Katrina Ji

---

### Teammate: Yuchen Wang, Katrina Ji

---

# Screenshot of Boot PIN register Reading:

<img width="1082" alt="Screen Shot 2022-11-11 at 22 08 37" src="https://user-images.githubusercontent.com/105755054/201453746-23ed6d07-f0f8-443a-bc06-77b606b4ea56.png">


# Screenshot of Writing Mode with Mask:

<img width="1082" alt="Screen Shot 2022-11-11 at 22 09 58" src="https://user-images.githubusercontent.com/105755054/201453786-43de20f2-e0e8-49c9-b226-d714a08d488b.png">

---

# Modified Parts:

- Input Function:

```
char line[MaxLen + 1];
void ReadLine(void){
    uint idx = 0;
    while(1){
        char c = getchar_timeout_us(0);
        
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

```

  In this section, the main issue is how to read a 32_bits Hexdecimal address. I creadte a ``` ReadLine ``` function with ``` getchar_timeout_us() ``` to read a line of 32-bits address. I have tried to use ``` scanf() ```, but it looks like cannot work correcly. This function will return an array or so called string to the ```main()``` function, which cannot enter as address with type of string. So, we have to use another function that can convert string to real hex number.
  
  ```
  user_input = (long int)strtoul(line, NULL, 16);

  ```
  
 - Note that when we define the max length of array, we can not use 8 bits, beacuse it will over flow, whatever you type in a string with 8bits, it will return '0xffffffff'. Also you are better to use ``` strtoul()``` instead of ``` strtol()```.
 
 ---
 
 # Explain:
 For  ``` getchar_timeout_us() ``` that rp2040 build-in function, it can only read a character each loop, so we have to design a funciton than can read a string with 8 bits length. This function is an infinity loop function until you type 'enter' and this string will return to ```main()``` then converting to the hexdecimal. Since there is a ``` register.h``` , we can use ``` #include "register.h" ``` to find the value of each address directly.
 
