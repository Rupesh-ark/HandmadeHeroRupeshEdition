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

LRESULT CALLBACK WindowProc(HWND window,
  UINT    message,
  WPARAM  wParam,
  LPARAM  lParam)
{
    LRESULT result = 0;
    switch(message)    //Using Blocks with cases to prevent variable leakage
    {
      case WM_SIZE: // If the window size changes
      {
          OutputDebugStringA("WM_SIZE\n");
      }break;
      case WM_DESTROY: //If windows destroys the window
      {
          OutputDebugStringA("WM_DESTROY\n");
      }break;
      case WM_CLOSE: // If user clicks the x button
      {
          OutputDebugStringA("WM_CLOSE\n");
      }break;
      case WM_ACTIVATEAPP: // To know if the window is active
      {
          OutputDebugStringA("WM_ACTIVATEAPP\n");
      }break;
      case WM_PAINT: // To Draw on the screen
      {
          PAINTSTRUCT paint;
          HDC deviceContext = BeginPaint(window, &paint); //This function will return deviceContext for drawing
          int X = paint.rcPaint.left;
          int Y = paint.rcPaint.top;
          LONG Height = paint.rcPaint.bottom - paint.rcPaint.top;
          LONG Width = paint.rcPaint.right - paint.rcPaint.left;
          static DWORD operation = WHITENESS;
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

int CALLBACK WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow)
{
  WNDCLASS windowClass = {};
  windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = hInstance;
  //WindowClass.hIcon;
  windowClass.lpszClassName = "HandMadeHeroWindowClass";
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
      for(;;)
      {
          BOOL messageResult = GetMessage(&message,0,0,0);
          if(messageResult>0)
          {
            TranslateMessage(&message); //Windows thing to convert keyboard messages into proper formatted keyboard message
            DispatchMessage(&message);

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
    // Error Handling
  }

//  MessageBoxA(0, "This is HandMadeHeroRupeshEdition", "HandMadeHero",MB_OK|MB_ICONINFORMATION);
  return (0);
}
