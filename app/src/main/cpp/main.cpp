#include <jni.h>

#include "AndroidOut.h"
#include "Renderer.h"

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

#include <iostream>
#include <cmath>
#include <string>

    using namespace std;

/*!
 * Handles commands sent to this Android application
 * @param pApp the app the commands are coming from
 * @param cmd the command to handle
 */
void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            // A new window is created, associate a renderer with it. You may replace this with a
            // "game" class if that suits your needs. Remember to change all instances of userData
            // if you change the class here as a reinterpret_cast is dangerous this in the
            // android_main function and the APP_CMD_TERM_WINDOW handler case.
            pApp->userData = new Renderer(pApp);
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being destroyed. Use this to clean up your userData to avoid leaking
            // resources.
            //
            // We have to check if userData is assigned just in case this comes in really quickly
            if (pApp->userData) {
                //
                auto *pRenderer = reinterpret_cast<Renderer *>(pApp->userData);
                pApp->userData = nullptr;
                delete pRenderer;
            }
            break;
        default:
            break;
    }
}

/*!
 * Enable the motion events you want to handle; not handled events are
 * passed back to OS for further processing. For this example case,
 * only pointer and joystick devices are enabled.
 *
 * @param motionEvent the newly arrived GameActivityMotionEvent.
 * @return true if the event is from a pointer or joystick device,
 *         false for all other input devices.
 */
bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

/*!
 * This the main entry point for a native activity
 */


void rps();

int main() {
    cout << "Execute rps() function to play game. Enter a number" << endl;
    int choice;
    cin >> choice;
    rps();
}

}