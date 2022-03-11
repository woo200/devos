#include "KSC1.hpp";

/**
 * @brief Translate a PS/1 KSC1 scan code into a {@code KeyInput}
 * 
 * @param scanCode Scancode to translate
 * @return KeyInput translated key
 */
KeyInput translateScanCode(uint8_t scanCode)
{
    KeyInput keyInput;

    keyInput.action = KeyDown;

    if (scanCode >= 0x81) {
        scanCode -= 0x80;
        keyInput.action = KeyUp;
    }

    keyInput.key = scanCodeTable[scanCode];
    return keyInput;
}

/**
 * @brief Translate key-code into char - Returns 0 if key is not a letter
 * 
 * @param keyCode Keycode to translate
 * @return char Translated char
 */
char translateKeyCode(KSC1 keyCode)
{
    switch (keyCode)
    {
    case NUM1:
        return '1';
    case NUM2:
        return '2';
    case NUM3:
        return '3';
    case NUM4:
        return '4';
    case NUM5:
        return '5';
    case NUM6:
        return '6';
    case NUM7:
        return '7';
    case NUM8:
        return '8';
    case NUM9:
        return '9';
    case NUM0:
        return '0';
    case Minus:
        return '-';
    case Equals:
        return '=';
    case KeyA:
        return 'A';
    case KeyB:
        return 'B';
    case KeyC:
        return 'C';
    case KeyD:
        return 'D';
    case KeyE:
        return 'E';
    case KeyF:
        return 'F';
    case KeyG:
        return 'G';
    case KeyH:
        return 'H';
    case KeyI:
        return 'I';
    case KeyJ:
        return 'J';
    case KeyK:
        return 'K';
    case KeyL:
        return 'L';
    case KeyM:
        return 'M';
    case KeyN:
        return 'N';
    case KeyO:
        return 'O';
    case KeyP:
        return 'P';
    case KeyQ:
        return 'Q';
    case KeyR:
        return 'R';
    case KeyS:
        return 'S';
    case KeyT:
        return 'T';
    case KeyU:
        return 'U';
    case KeyV:
        return 'V';
    case KeyW:
        return 'W';
    case KeyX:
        return 'X';
    case KeyY:
        return 'Y';
    case KeyZ:
        return 'Z';
    case OpenBracket:
        return '[';
    case CloseBracket:
        return ']';
    case Enter:
        return '\n';
    case Semicolon:
        return ';';
    case Quote:
        return '"';
    case Backtick:
        return '`';
    case Comma:
        return ',';
    case Period:
        return '.';
    case Slash:
        return '/';
    case NumpadAsterisk:
        return '*';
    case Space:
        return ' ';
    case Numpad0:
        return '0';
    case Numpad1:
        return '1';
    case Numpad2:
        return '2';
    case Numpad3:
        return '3';
    case Numpad4:
        return '4';
    case Numpad5:
        return '5';
    case Numpad6:
        return '6';
    case Numpad7:
        return '7';
    case Numpad8:
        return '8';
    case Numpad9:
        return '9';
    case NumpadMinus:
        return '-';
    case NumpadPlus:
        return '+';
    case NumpadPeriod:
        return '.';
    default:
        return 0;
    }
}