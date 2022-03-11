#pragma once

#include "../types.hpp"

/**
 * @brief Keyboard Scan Code Set #1 https://wiki.osdev.org/PS/2_Keyboard#Scan_Code_Set_1
 * 
 */
enum KSC1 {
    Escape, NUM1, NUM2, NUM3, NUM4, NUM5,
    NUM6, NUM7, NUM8, NUM9, NUM0, Minus,
    Equals, Backspace, Tab, KeyQ, KeyW,
    KeyE, KeyR, KeyT, KeyY, KeyU, KeyI,
    KeyO, KeyP, OpenBracket, CloseBracket, 
    Enter, LeftCtrl, KeyA, KeyS, KeyD,
    KeyF, KeyG, KeyH, KeyJ, KeyK, KeyL,
    Semicolon, Quote, Backtick, LeftShift, 
    Backslash, KeyZ, KeyX, KeyC, KeyV,
    KeyB, KeyN, KeyM, Comma, Period, Slash,
    RightShift, NumpadAsterisk, LeftAlt,
    Space, CapsLock, F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, NumLock, ScrollLock,
    Numpad7, Numpad8, Numpad9, NumpadMinus,
    Numpad4, Numpad5, Numpad6, NumpadPlus,
    Numpad1, Numpad2, Numpad3, Numpad0,
    NumpadPeriod, // 0x53 --- 0x57
    F11, F12 // 0x58 - 0x81
};

const KSC1 scanCodeTable[] = {
    Escape, Escape, NUM1, NUM2, NUM3, NUM4, NUM5,
    NUM6, NUM7, NUM8, NUM9, NUM0, Minus,
    Equals, Backspace, Tab, KeyQ, KeyW,
    KeyE, KeyR, KeyT, KeyY, KeyU, KeyI,
    KeyO, KeyP, OpenBracket, CloseBracket, 
    Enter, LeftCtrl, KeyA, KeyS, KeyD,
    KeyF, KeyG, KeyH, KeyJ, KeyK, KeyL,
    Semicolon, Quote, Backtick, LeftShift, 
    Backslash, KeyZ, KeyX, KeyC, KeyV,
    KeyB, KeyN, KeyM, Comma, Period, Slash,
    RightShift, NumpadAsterisk, LeftAlt,
    Space, CapsLock, F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, NumLock, ScrollLock,
    Numpad7, Numpad8, Numpad9, NumpadMinus,
    Numpad4, Numpad5, Numpad6, NumpadPlus,
    Numpad1, Numpad2, Numpad3, Numpad0,
    NumpadPeriod, 
    
    Escape, Escape, Escape,
    
    F11, F12
};

/**
 * @brief 
 * 
 */
enum KeyAction {
    KeyDown,
    KeyUp
};

/**
 * @brief Describes a keypress
 * 
 */
struct KeyInput {
    KeyAction action;
    KSC1 key;
};

KeyInput translateScanCode(uint8_t scanCode);
char translateKeyCode(KSC1 keyCode);