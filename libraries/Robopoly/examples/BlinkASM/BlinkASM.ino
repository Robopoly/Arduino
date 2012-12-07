/***************************************************************************************
 *
 * Title:       BlinkASM
 * Description: Blink the onboard LED, written in assembly code.
 *
 ***************************************************************************************/

// delay function for 500ms
asm(
  "_delay:              \n\t"
  "LDI    r26, 85       \n\t"
  "LDI    r27, 64       \n\t"
  "LDI    r28, 255      \n\t"
  "_count:              \n\t"
  "DEC    r26           \n\t"
  "BRNE   _count        \n\t"
  "LDI    r26, 85       \n\t"
  "DEC    r27           \n\t"
  "BRNE   _count        \n\t"
  "LDI    r27, 64       \n\t"
  "DEC    r28           \n\t"
  "brne   _count        \n\t"
  "RET                  \n\t"
);

int main()
{
  // set LED port as output (DDRC = 0x14)
  asm("SBI    0x14, 2   \n\t");
  
  // toggle LED (PORTC = 0x15) inside infinite loop
  asm(
    "_loop:\n\t"
    "SBI    0x15, 2     \n\t"
    "RCALL  _delay      \n\t"
    "CBI    0x15, 2     \n\t"
    "RCALL  _delay      \n\t"
    "RJMP   _loop       \n\t"
  );
}

