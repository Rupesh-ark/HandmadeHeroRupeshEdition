/**
 * @Author: Rupesh Pandey <Rupesh_ark>
 * @Date:   2020-10-16T01:42:12+05:30
 * @Email:  pandeyrupesh00@gmail.com
 * @Project: HandMadeHeroRupeshEdition
 * @Filename: win32_handmade.cpp
 * @Last modified by: Rupesh Pandey
 * @Last modified time: 2020-10-20T01:19:21+05:30
 */
#include <windows.h>

//To understand the different meanings of static

#define internal static
#define local_persist static
#define global_variable static

global_variable bool runningApplication; //This is global for now

internal void ResizeDIBSection()   //To create or change the DIB(device-independent bitmap) section
{

}

LRESULT CALLBACK WindowProc(HWND window, UINT    message, WPARAM  wParam,LPARAM  lParam)
{
    LRESULT result = 0;
    switch(message)    //Using Blocks with cases to prevent variable leakage
    {
      case WM_SIZE: // If the window size changes
      {
        ResizeDIBSection();
      }break;
      case WM_CLOSE: // If user clicks the x button
      {
          //Handling this in the future by sending a message to the user
          runningApplication = false;

      }break;
      case WM_ACTIVATEAPP: // To know if the window is active
      {

      }break;
      case WM_DESTROY: //If windows destroys the window
      {
          //Treat this as an error if for some reason the window gets destroyed, recreate window later.
          runningApplication = false;
      }break;
      case WM_PAINT: // To Draw on the screen
      {
          PAINTSTRUCT paint;
          HDC deviceContext = BeginPaint(window, &paint); //This function will return deviceContext for drawing

          int X = paint.rcPaint.left;
          int Y = paint.rcPaint.top;
          LONG Height = paint.rcPaint.bottom - paint.rcPaint.top;
          LONG Width = paint.rcPaint.right - paint.rcPaint.left;

          local_persist DWORD operation = WHITENESS;  // This data will persist and will not initialize the variable
          PatBlt(deviceContext, X, Y, Width, Height, operation);  // to paint the window
          EndPaint(window,&paint);
      }break;
      default:
      {
        result = DefWindowProcA(window, message, wParam, lParam); //Let Windows handle the default cases;
          //OutputDebugStringA("Default\n");
      }break;
    }
    return (result);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
  WNDCLASS windowClass = {};
  windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW; // Set of binary flags to tell windows what kind of property we want to have

  windowClass.lpfnWndProc = WindowProc; //Pointer to a function that we will define, that defines how our window will respond to events

  //WindowClass.cbClsExtra if we want extra bytes along with the window class; we don't need this here
  //WindowClass.cbWndExtra if we want extra bytes with the window that we create

  windowClass.hInstance = hInstance; // What instance is setting the window

  //WindowClass.hIcon; Will set this later
  //WindowClass.hCursor; Will not need a Cursor
  //WindowClass.hbrBackground; We don't need to clear our background
  //windowClass.lpszMenuName; We don't want windows menu


  windowClass.lpszClassName = "HandMadeHeroWindowClass";  //Name of windowClass, using this name we can create a window
  if(RegisterClass(&windowClass))
  {
    HWND windowHandle = CreateWindowExA(
                        0,
                        windowClass.lpszClassName,
                        "HandMadeHeroRupeshEdition",
                        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        0,
                        0,
                        hInstance,
                        0);
    if(windowHandle)
    {
      MSG message;
      runningApplication = true;
      while(runningApplication)
      {
          BOOL messageResult = GetMessage(&message,0,0,0);
          if(messageResult>0)
          {
            TranslateMessage(&message); //Windows thing to convert keyboard messages into proper formatted keyboard message.
            DispatchMessage(&message);  //To dispatch the message to windows to handle, Yes we don't have control over the messages.
          }
          else
          {
            break;
          }
      }
    }
    else
    {
      // Error Handling
    }
  }
  else
  {
    //Error Handling
  }

//MessageBoxA(0, "This is HandMadeHeroRupeshEdition", "HandMadeHero",MB_OK|MB_ICONINFORMATION);
  return (0);
}
