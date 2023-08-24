#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_RESULT 100
#define ID_BUTTON_DIGIT 101
#define ID_BUTTON_ADD 111
#define ID_BUTTON_SUBTRACT 112
#define ID_BUTTON_MULTIPLY 113
#define ID_BUTTON_DIVIDE 114
#define ID_BUTTON_EQUALS 115
#define ID_BUTTON_CLEAR 116

HFONT hFont;

// Variables para almacenar los n�meros y la operaci�n
char firstNumber[20] = ""; // Primer n�mero
char currentNumber[20] = "0"; // N�mero actual (visor)
char operation[2] = ""; // Operaci�n seleccionada (+, -, *, /)
int selectedOperation = -1; // Variable para almacenar la operaci�n seleccionada

// Arreglo de operadores
const char *operators[] = { "+", "-", "*", "/" };

// Funci�n para actualizar el visor
void UpdateDisplay(HWND hwnd)
{
    char displayText[100];
    sprintf(displayText, "%s %s %s", firstNumber, operation, currentNumber);
    SetWindowText(hwnd, displayText);
}

// Funci�n para realizar el c�lculo
void PerformCalculation()
{
    // Convertir los n�meros a valores flotantes
    float num1 = atof(firstNumber);
    float num2 = atof(currentNumber);

    // Realizar la operaci�n seg�n la operaci�n seleccionada
    if (strcmp(operation, "+") == 0) {
        num1 += num2;
    } else if (strcmp(operation, "-") == 0) {
        num1 -= num2;
    } else if (strcmp(operation, "*") == 0) {
        num1 *= num2;
    } else if (strcmp(operation, "/") == 0) {
        if (num2 != 0) {
            num1 /= num2;
        } else {
            // Manejar la divisi�n por cero aqu� si es necesario
        }
    }

    // Actualizar el visor con el resultado
    sprintf(currentNumber, "%.2f", num1);
    strcpy(firstNumber, currentNumber); // Actualizar el primer n�mero
}

// Funci�n para crear los controles de la calculadora
void CreateControls(HWND hwnd)
{
    // Calcular las posiciones de los controles
    int control_width = 60;
    int control_height = 60;
    int button_padding = 10;
    int button_start_x = 50;
    int button_start_y = 150;
    int row_size = 4;

    // Crear el visor
    HWND hwndResult = CreateWindow("STATIC", "0", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
        button_start_x, 50, 300, 60, hwnd, (HMENU)ID_RESULT, GetModuleHandle(NULL), NULL);
    SendMessage(hwndResult, WM_SETFONT, (WPARAM)hFont, TRUE);

    // Crear los botones num�ricos
    char buttonText[2];
    for (int i = 0; i <= 9; i++)
    {
        int row = i / row_size;
        int col = i % row_size;
        int x = button_start_x + col * (control_width + button_padding);
        int y = button_start_y + row * (control_height + button_padding);

        sprintf(buttonText, "%d", i);
        CreateWindow("BUTTON", buttonText, WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            x, y, control_width, control_height, hwnd, (HMENU)(ID_BUTTON_DIGIT + i), GetModuleHandle(NULL), NULL);
    }

    // Crear los botones de operaciones
    for (int i = 0; i < 4; i++) {
        int x = button_start_x + row_size * (control_width + button_padding) + button_padding;
        int y = button_start_y + i * (control_height + button_padding);
        CreateWindow("BUTTON", operators[i], WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            x, y, control_width, control_height, hwnd, (HMENU)(ID_BUTTON_ADD + i), GetModuleHandle(NULL), NULL);
    }

    // Crear el bot�n de igual y el bot�n de borrar
    int x_equals = button_start_x + row_size * (control_width + button_padding) + button_padding;
    int y_equals = button_start_y + 4 * (control_height + button_padding);
    CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        x_equals, y_equals, control_width, control_height, hwnd, (HMENU)ID_BUTTON_EQUALS, GetModuleHandle(NULL), NULL);

    int x_clear = button_start_x;
    int y_clear = button_start_y + 4 * (control_height + button_padding);
    CreateWindow("BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        x_clear, y_clear, control_width, control_height, hwnd, (HMENU)ID_BUTTON_CLEAR, GetModuleHandle(NULL), NULL);
}

// Funci�n principal de la ventana
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        CreateControls(hwnd); // Llamar a la funci�n para crear los controles
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BUTTON_DIGIT:
            // Manejar clic en bot�n num�rico
            {
                int digit = LOWORD(wParam) - ID_BUTTON_DIGIT; // Obtener el d�gito del bot�n
                if (strcmp(currentNumber, "0") == 0) {
                    // Si el visor muestra 0, reemplazarlo con el d�gito seleccionado
                    sprintf(currentNumber, "%d", digit);
                }
                else {
                    // Concatenar el d�gito al n�mero actual en el visor
                    char temp[20];
                    strcpy(temp, currentNumber);
                    sprintf(currentNumber, "%s%d", temp, digit);
                }
                UpdateDisplay(GetDlgItem(hwnd, ID_RESULT));
            }
            break;
        case ID_BUTTON_ADD:
        case ID_BUTTON_SUBTRACT:
        case ID_BUTTON_MULTIPLY:
        case ID_BUTTON_DIVIDE:
            // Manejar clic en bot�n de operaci�n
            // Almacenar la operaci�n seleccionada
            strcpy(firstNumber, currentNumber);
            selectedOperation = LOWORD(wParam);
            strcpy(currentNumber, "0"); // Restablecer el visor a 0
            strcpy(operation, operators[selectedOperation - ID_BUTTON_ADD]);
            UpdateDisplay(GetDlgItem(hwnd, ID_RESULT));
            break;
        case ID_BUTTON_EQUALS:
            // Manejar clic en el bot�n de igual
            // Realizar el c�lculo y mostrar el resultado en el visor
            PerformCalculation();
            UpdateDisplay(GetDlgItem(hwnd, ID_RESULT));
            break;
        case ID_BUTTON_CLEAR:
            // Manejar clic en el bot�n de borrar (C)
            // Limpiar el visor y restablecer las variables
            strcpy(currentNumber, "0");
            strcpy(firstNumber, "");
            strcpy(operation, "");
            selectedOperation = -1; // Restablecer la operaci�n
            UpdateDisplay(GetDlgItem(hwnd, ID_RESULT));
            break;
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

// Funci�n principal del programa
int main()
{
    const char *CLASS_NAME = "SampleWindowClass";
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Fondo blanco

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                               // Optional window styles.
        CLASS_NAME,                      // Window class
        NULL,                            // T�tulo vac�o
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, // Estilo de ventana
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 600, // Dimensiones de la ventana
        NULL,       // Ventana principal
        NULL,       // Men�
        hInstance,  // Instancia de la aplicaci�n
        NULL        // Datos adicionales
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Cambiar el t�tulo de la ventana
    SetWindowText(hwnd, "FACUBROS CALCULATOR");

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

