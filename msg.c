#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//FOO STATE MANAGEMENT
enum STATE_FOO
{
    FOO_STATE1 = 1,
    FOO_STATE2 = 2,
    FOO_STATE3 = 3,
    FOO_FINAL = 4
};
enum STATE_FOO foo_state = FOO_STATE1;
enum STATE_FOO state_foo(char c, enum STATE_FOO currentState);
int foo(char *userText);
int eep(char *userText);
int op(char *userText);
int ork(char *userText);

//EEP STATE MANAGEMENT
enum STATE_EEP
{
    EEP_STATE1 = 1,
    EEP_STATE3 = 3,
    EEP_FINAL = 2
};
enum STATE_EEP eep_state = EEP_STATE1;
enum STATE_EEP state_eep(char c, enum STATE_EEP currentState);

//OP STATE MANAGEMENT
enum STATE_OP
{
    OP_STATE1 = 1,
    OP_STATE2 = 2,
    OP_FINAL = 3
};

enum STATE_OP op_state = OP_STATE1;
enum STATE_OP state_op(char c, enum STATE_OP currentState);

//ORK STATE MANAGEMENT
enum STATE_ORK
{
    ORK_STATE1 = 1,
    ORK_STATE2 = 2,
    ORK_STATE_EF = 3,
    ORK_STATE_E3 = 4,
    ORK_STATE_F2 = 5,
    ORK_STATE_F3 = 6,
    ORK_STATE_FF = 7
};
enum STATE_ORK ork_state = ORK_STATE1;
enum STATE_ORK state_ork(char c, enum STATE_ORK currentVal, int countedLength);
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        char text[100];
        printf("Type a line of text here:");
        scanf("%s", text);
        if (text[0] == 'E')
        {
            if (foo(text))
            {
                printf("%s OK", text);
            }
            else
            {
                printf("%s FAIL", text);
            };
        };
        if (text[0] == 'P')
        {
            if (eep(text))
            {
                printf("%s OK", text);
            }
            else
            {
                printf("%s FAIL", text);
            };
        };
        if (text[0] == 'Q')
        {
            if (op(text))
            {
                printf("%s OK\n", text);
            }
            else
            {
                printf("%s FAIL\n", text);
            };
        };
        if (text[0] == 'M')
        {
            if (ork(text))
            {
                printf("%s OK\n", text);
            }
            else
            {
                printf("%s FAIL\n", text);
            };
        };
    }
    else
    {
        char text[100];
        FILE *fPointer = fopen(argv[1], "r");
        if (fPointer == NULL)
        {
            printf("Cannot open the file\n");
            return 0;
        }
        while (!feof(fPointer))
        {
            fgets(text, 255, fPointer);
            if (text[0] == 'E')
            {
                if (foo(text))
                {
                    printf("%s OK\n", text);
                }
                else
                {
                    printf("%s FAIL\n", text);
                };
            };

            if (text[0] == 'P')
            {
                if (eep(text))
                {
                    printf("%s OK\n", text);
                }
                else
                {
                    printf("%s FAIL\n", text);
                };
            };

            if (text[0] == 'Q')
            {
                if (op(text))
                {
                    printf("%s OK\n", text);
                }
                else
                {
                    printf("%s FAIL\n", text);
                };
            };
            if (text[0] == 'M')
            {
                if (ork(text))
                {
                    printf("%s OK\n", text);
                }
                else
                {
                    printf("%s FAIL\n", text);
                };
            };
        }
        fclose(fPointer);
    }
}
// int main(int argc, char* argv[]) {
//         FILE* f;
//         char c;
//         if (argc == 1) {
//                 f = stdin;
//         }
//         else {
//                 f = fopen(argv[1], "r");
//                 if (f == NULL) {
//                         printf("Cannot open file");
//                 }
//         }
// }
int ork(char *userText)
{

    size_t length = strlen(userText);
    size_t x = 3;
    if (userText[0] == 'M')
    {
        ork_state = ORK_STATE2;
    }
    if (isdigit((int)(userText[1])) && isdigit((int)(userText[2])))
    {
        ork_state = ORK_STATE2;
        char *tempStr = userText + 3;
        if (userText[3] == 'E')
        {
            if (foo(tempStr))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (userText[3] == 'P')
        {
            if (eep(tempStr))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}
int foo(char *userText)
{

    size_t length = strlen(userText);
    size_t x = 0;
    for (; x < length; x++)
    {

        char currentVal = userText[x];
        if (foo_state == FOO_STATE1)
        {
            foo_state = state_foo(currentVal, FOO_STATE1);
        }
        else if (foo_state == FOO_STATE2)
        {
            foo_state = state_foo(currentVal, FOO_STATE2);
        }
        else if (foo_state == FOO_STATE3)
        {
            foo_state = state_foo(currentVal, FOO_STATE3);
        }
    }
    if (foo_state == FOO_FINAL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

enum STATE_FOO state_foo(char c, enum STATE_FOO currentState)

{
    if (currentState == FOO_STATE1)
    {
        if (c == 'E')
            foo_state = FOO_STATE2;
        else
            foo_state = FOO_STATE1;
        return foo_state;
    }
    if (currentState == FOO_STATE2)
    {
        if (c == '1' || c == '2' || c == '0')
        {
            foo_state = FOO_STATE3;
        }
        if (c == 'E')
        {
            foo_state = FOO_STATE2;
        }
        return foo_state;
    }
    if (currentState == FOO_STATE3)
    {
        if (c == '1' || c == '2' || c == '0')
        {
            foo_state = FOO_STATE3;
        }
        if (c == 'F')
        {
            foo_state = FOO_FINAL;
        }
        return foo_state;
    }
    return foo_state;
}

int op(char *userText)
{
    size_t length = strlen(userText);
    size_t x = 0;
    for (; x < length; x++)
    {

        char currentVal = userText[x];
        if (op_state == OP_STATE1)
        {
            op_state = state_op(currentVal, op_state);
        }
        else if (op_state == OP_STATE2)
        {
            op_state = state_op(currentVal, op_state);
        }
        else if (op_state == OP_FINAL)
        {
            op_state = state_op(currentVal, op_state);
        }
    }

    if (op_state == OP_FINAL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

enum STATE_OP state_op(char c, enum STATE_OP currentState)
{
    if (currentState == OP_STATE1)
    {
        if (c == 'Q')
        {
            op_state = OP_STATE2;
            return op_state;
        }
    }
    if (currentState == OP_STATE2)
    {
        if (c == '6')
        {
            op_state = OP_STATE2;
            return op_state;
        }
        else if (c == '7')
        {
            op_state = OP_FINAL;
            return op_state;
        }
    }
    if (currentState == OP_FINAL)
    {
        if (c == '6')
        {
            op_state = OP_FINAL;
            return op_state;
        }
        else if (c == '7')
        {
            op_state = OP_STATE2;
            return op_state;
        }
    }
    return op_state;
}

int eep(char *userText)
{
    size_t length = strlen(userText);
    size_t x = 0;
    for (; x < length; x++)
    {
        char currentVal = userText[x];
        if (eep_state == EEP_STATE1)
        {
            eep_state = state_eep(currentVal, EEP_STATE1);
        }
        else if (eep_state == EEP_FINAL)
        {
            eep_state = state_eep(currentVal, EEP_FINAL);
        }
        else if (eep_state == EEP_STATE3)
        {
            eep_state = state_eep(currentVal, EEP_STATE3);
        }
    }
    if (eep_state == EEP_FINAL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

enum STATE_EEP state_eep(char c, enum STATE_EEP currentState)
{
    if (currentState == EEP_STATE1)
    {
        if (c == 'P')
        {
            eep_state = EEP_FINAL;
            return eep_state;
        }
        else
        {
            eep_state = EEP_STATE1;
            return eep_state;
        }
    }
    if (currentState == EEP_FINAL)
    {
        if (c == 'B')
        {
            eep_state = EEP_STATE3;
            return eep_state;
        }
    }
    if (currentState == EEP_STATE3)
    {
        if (c == 'C')
        {
            eep_state = EEP_FINAL;
            return eep_state;
        }
    }
    return eep_state;
}
