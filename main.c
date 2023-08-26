#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_INPUT1 101
#define ID_INPUT2 102
#define ID_RESULT 103
#define ID_BUTTON_ADD 111
#define ID_BUTTON_SUBTRACT 112
#define ID_BUTTON_MULTIPLY 113
#define ID_BUTTON_DIVIDE 114
#define ID_BUTTON_CLEAR 115
#define ID_BUTTON_EQUALS 116
#define ID_BUTTON_ROOT 117
#define ID_BUTTON_POWER 118
#define ID_BUTTON_PORC 119
#define ID_BUTTON_LOG 120
#define IDM_CALCULADORA 1
#define IDM_RESOLVENTE 2

HFONT hFont;

// Variables para almacenar los números y la operación
char number1[20] = "";
char number2[20] = "";
char operation[2] = ""; // Operación seleccionada (+, -, *, /)
HWND hwndInput1;
HWND hwndInput2;
HWND hwndResult;
int selectedOperation = -1; // Variable para almacenar la operación seleccionada

// Arreglo de operadores
const char *operators[] = { "+", "-", "*", "/" };

// Función para actualizar el visor
void UpdateDisplay(HWND hwnd, const char *text)
{
    SetWindowText(hwnd, text);
}

// Función para realizar el cálculo
float PerformCalculation()
{
    // Convertir los números a valores flotantes
    float num1 = atof(number1);
    float num2 = atof(number2);

    // Realizar la operación según la operación seleccionada
    if (strcmp(operation, "+") == 0)
    {
        return num1 + num2;
    }
    else if (strcmp(operation, "-") == 0)
    {
        return num1 - num2;
    }
    else if (strcmp(operation, "*") == 0)
    {
        return num1 * num2;
    }
    else if (strcmp(operation, "/") == 0)
    {
        if (num2 != 0)
        {
            return num1 / num2;
        }
        else
        {
            return 9999;
        }
    }
    return 0;
}

void CreateControls(HWND hwnd)
{
    // Calcular las posiciones de los controles
    int control_width = 80;
    int control_height = 30;
    int control_padding = 10;
    int button_width = 60;
    int button_height = 60;
    int button_padding = 10;
    int button_start_x = 10; // Ajustar el margen izquierdo
    int button_start_y = 150;
    int row_size = 4;

    // Obtener las dimensiones de la ventana principal
    RECT rect;
    GetClientRect(hwnd, &rect);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

// Calcular las coordenadas para el centro de la ventana
    int centerX = windowWidth / 2;

// Calcular las coordenadas para los controles de entrada y el visor
    int inputWidth = control_width;
    int inputHeight = control_height;

    int input1X = centerX - inputWidth - control_padding;
    int input1Y = 50; // No cambiar la coordenada Y

    int input2X = centerX - inputWidth - control_padding;
    int input2Y = 100; // No cambiar la coordenada Y

    int resultX = centerX + control_padding;
    int resultY = 50; // No cambiar la coordenada Y

// Crear los controles de entrada
    hwndInput1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                              input1X, input1Y, inputWidth, inputHeight, hwnd, (HMENU)ID_INPUT1, GetModuleHandle(NULL), NULL);
    SendMessage(hwndInput1, WM_SETFONT, (WPARAM)hFont, TRUE);

    hwndInput2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                              input2X, input2Y, inputWidth, inputHeight, hwnd, (HMENU)ID_INPUT2, GetModuleHandle(NULL), NULL);
    SendMessage(hwndInput2, WM_SETFONT, (WPARAM)hFont, TRUE);

// Crear el visor
    hwndResult = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | SS_CENTER,
                              resultX, resultY, inputWidth, 2 * inputHeight, hwnd, (HMENU)ID_RESULT, GetModuleHandle(NULL), NULL);
    SendMessage(hwndResult, WM_SETFONT, (WPARAM)hFont, TRUE);

    // Calcular el espacio entre los botones
    int horizontal_spacing = (400 - 2 * button_start_x - row_size * button_width) / (row_size - 1);

// Crear los botones de operaciones
    for (int i = 0; i < 4; i++)
    {
        int x = button_start_x + i * (button_width + button_padding);
        int y = button_start_y;
        CreateWindow("BUTTON", operators[i], WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                     x, y, button_width, button_height, hwnd, (HMENU)(ID_BUTTON_ADD + i), GetModuleHandle(NULL), NULL);
    }

// Crear el botón de borrar todo
    int x_clear = button_start_x + 4 * (button_width + button_padding);
    int y_clear = button_start_y;
    CreateWindow("BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                 x_clear, y_clear, button_width, button_height, hwnd, (HMENU)ID_BUTTON_CLEAR, GetModuleHandle(NULL), NULL);
    /*
    // Crear el botón de igual
        int x_equals = button_start_x + 4 * (button_width + button_padding);
        int y_equals = button_start_y + button_height + button_padding;
        CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                     x_equals, y_equals, button_width, button_height, hwnd, (HMENU)ID_BUTTON_EQUALS, GetModuleHandle(NULL), NULL);
    */
// Crear el botón de raiz
    int x_root = button_start_x; // Inicio de una nueva fila
    int y_root = button_start_y + 75;
    CreateWindow("BUTTON", "Raiz", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                 x_root, y_root, button_width, button_height, hwnd, (HMENU)ID_BUTTON_ROOT, GetModuleHandle(NULL), NULL);

// Crear el botón de potencia
    int x_power = x_root + button_width + button_padding; // Siguiente posición en la misma fila
    int y_power = y_root;
    CreateWindow("BUTTON", "Pot", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                 x_power, y_power, button_width, button_height, hwnd, (HMENU)ID_BUTTON_POWER, GetModuleHandle(NULL), NULL);

// Crear el botón de PORCENTAJE
    int x_porc = x_power + button_width + button_padding; // Siguiente posición en la misma fila
    int y_porc = y_root;
    CreateWindow("BUTTON", "%", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                 x_porc, y_porc, button_width, button_height, hwnd, (HMENU)ID_BUTTON_PORC, GetModuleHandle(NULL), NULL);

    // Crear el botón de LOGARITMO
    int x_log = x_porc + button_width + button_padding; // Siguiente posición en la misma fila
    int y_log = y_root;
    CreateWindow("BUTTON", "Log", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                 x_log, y_log, button_width, button_height, hwnd, (HMENU)ID_BUTTON_LOG, GetModuleHandle(NULL), NULL);

}

// Función principal de la ventana
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
    {
        // Crear el menú principal
        HMENU hMenu = CreateMenu();

        // Crear un menú desplegable "Modos"
        HMENU hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, IDM_CALCULADORA, "Calculadora"); // Agregar la opción "Calculadora"
        AppendMenu(hSubMenu, MF_STRING, IDM_RESOLVENTE, "Resolvente");   // Agregar la opción "Resolvente"

        // Agregar el menú desplegable "Modos" al menú principal
        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Modos");

        // Asignar el menú a la ventana
        SetMenu(hwnd, hMenu);

        // Registrar las opciones de menú como mensajes
        RegisterHotKey(hwnd, IDM_CALCULADORA, 0, VK_F1); // Atajo de teclado para "Calculadora"
        RegisterHotKey(hwnd, IDM_RESOLVENTE, 0, VK_F2); // Atajo de teclado para "Resolvente"


        CreateControls(hwnd); // Llamar a la función para crear los controles
        break;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case ID_BUTTON_ADD:
            case ID_BUTTON_SUBTRACT:
            case ID_BUTTON_MULTIPLY:
            case ID_BUTTON_DIVIDE:
                // Manejar clic en botón de operación
                // Almacenar la operación seleccionada
                GetWindowText(hwndInput1, number1, sizeof(number1));
                GetWindowText(hwndInput2, number2, sizeof(number2));
                selectedOperation = LOWORD(wParam);
                strcpy(operation, operators[selectedOperation - ID_BUTTON_ADD]);

                // Realizar el cálculo y mostrar el resultado en el visor
                float result = PerformCalculation();
                char resultText[20];
                sprintf(resultText, "%.2f", result);
                UpdateDisplay(hwndResult, resultText);
                break;

            case ID_BUTTON_CLEAR:
                // Manejar clic en el botón de borrar todo
                SetWindowText(hwndInput1, "");
                SetWindowText(hwndInput2, "");
                strcpy(number1, "");
                strcpy(number2, "");
                strcpy(operation, "");
                UpdateDisplay(hwndResult, ""); // Limpiar el visor
                selectedOperation = -1; // Restablecer la operación
                break;
            /*
            case ID_BUTTON_EQUALS:
                // Manejar clic en el botón de igual
                GetWindowText(hwndInput1, number1, sizeof(number1));
                GetWindowText(hwndInput2, number2, sizeof(number2));

                // Realizar el cálculo y mostrar el resultado en el visor
                result = PerformCalculation();
                char resultTextEquals[20];
                sprintf(resultTextEquals, "%.2f", result);
                UpdateDisplay(hwndResult, resultTextEquals);
                break;
            */
            case ID_BUTTON_POWER:
                GetWindowText(hwndInput1, number1, sizeof(number1));
                GetWindowText(hwndInput2, number2, sizeof(number2));

                float base = atof(number1);
                int exponente = atoi(number2); // Convierte la cadena a un entero

                float resultado = 1.0; // Inicializa el resultado a 1.0

                for (int i = 1; i <= exponente; i++)
                {
                    resultado *= base;
                }

                resultText[20]; // Cadena para almacenar el resultado
                sprintf(resultText, "%.2f", resultado); // Convierte el resultado a una cadena

                UpdateDisplay(hwndResult, resultText); // Actualiza el visor con el resultado
                break;

            case ID_BUTTON_ROOT:
                GetWindowText(hwndInput1, number1, sizeof(number1));
                GetWindowText(hwndInput2, number2, sizeof(number2));

                float x = atof(number1); // Convierte la cadena a un número flotante
                int y = atoi(number2);   // Convierte la cadena a un número entero

                float r = 0;
                float z;
                int i;

                for (i = 1; i < x; i++)
                {
                    z = 1;

                    for (int j = 0; j < y; j++)
                    {
                        z *= i;
                    }

                    if (z == x)
                    {
                        r = i;
                        break;
                    }
                }

                resultText[20]; // Cadena para almacenar el resultado
                sprintf(resultText, "%.2f", r); // Convierte el resultado a una cadena

                UpdateDisplay(hwndResult, resultText); // Actualiza el visor con el resultado
                break;
            case ID_BUTTON_PORC:
                GetWindowText(hwndInput1, number1, sizeof(number1));
                GetWindowText(hwndInput2, number2, sizeof(number2));

                float num = atof(number1);
                int sobre = atoi(number2); // Convierte la cadena a un entero


                float porc_parc;
                porc_parc = (float) (num*sobre)/100;

                resultText[20]; // Cadena para almacenar el resultado
                sprintf(resultText, "%.2f", porc_parc); // Convierte el resultado a una cadena

                UpdateDisplay(hwndResult, resultText); // Actualiza el visor con el resultado
                break;
            case IDM_CALCULADORA:
                // Cambiar al modo "Calculadora"
                // Puedes realizar cualquier acción adicional necesaria aquí.
                // En este ejemplo, simplemente limpiamos las entradas y restauramos la operación a su estado predeterminado.
                SetWindowText(hwndInput1, "");
                SetWindowText(hwndInput2, "");
                strcpy(number1, "");
                strcpy(number2, "");
                strcpy(operation, "");
                UpdateDisplay(hwndResult, ""); // Limpiar el visor
                selectedOperation = -1; // Restablecer la operación
                break;

            case IDM_RESOLVENTE:
                // Cambiar al modo "Resolvente"
                // Puedes realizar cualquier acción adicional necesaria aquí para el modo "Resolvente".
                // Por ahora, simplemente mostramos un mensaje de aviso.
                MessageBox(hwnd, "Modo Resolvente seleccionado. Implementa la lógica aquí.", "Modo Resolvente", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;

        case WM_DESTROY:
            DeleteObject(hFont); // Liberar la fuente
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }
}
// Función principal del programa
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char *CLASS_NAME = "SampleWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Fondo blanco

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
                    0,                              // Estilos extendidos (ninguno en este caso)
                    CLASS_NAME,                     // Clase de la ventana
                    L"FACUBROS CALCULATOR",         // Título de la ventana
                    WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, // Estilo de la ventana (sin capacidad de redimensionamiento)
                    550,                            // Posición X de la ventana
                    170,                            // Posición Y de la ventana
                    367,                            // Ancho de la ventana
                    400,                            // Alto de la ventana
                    NULL,                           // Ventana padre (en este caso, no hay)
                    NULL,                           // Menú (en este caso, no hay)
                    hInstance,                      // Instancia de la aplicación
                    NULL                            // Datos adicionales de la aplicación
                );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Crear una fuente para el visor
    hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));



    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(hFont); // Liberar la fuente

    return 0;
}
