/*
  Новые функции в прошивке 1.2 описаны в README.MD
  Автор: Геннадий Дегтерёв, 2021
  gennadij@degterjow.de

  Скетч к проекту "Подсветка лестницы"
  Страница проекта (схемы, описания): https://alexgyver.ru/ledstairs/
  Исходники на GitHub: https://github.com/AlexGyver/LEDstairs
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

struct Step {
  int8_t led_amount;
  uint16_t night_mode_bitmask;  
};

// #define STRIP_LED_AMOUNT 34 // 2 STEPS
// #define STRIP_LED_AMOUNT 51 // 3 STEPS
// #define STRIP_LED_AMOUNT 68 // 4 STEPS
// #define STRIP_LED_AMOUNT 85 // 5 STEPS
// #define STRIP_LED_AMOUNT 102 // 6 STEPS
// #define STRIP_LED_AMOUNT 119 // 7 STEPS
// #define STRIP_LED_AMOUNT 138 // 8 STEPS
// #define STRIP_LED_AMOUNT 153 // 9 STEPS
// #define STRIP_LED_AMOUNT 170 // 10 STEPS
// #define STRIP_LED_AMOUNT 190 // 11 STEPS
// #define STRIP_LED_AMOUNT 198 // 12 STEPS
// #define STRIP_LED_AMOUNT 213 // 13 STEPS
// #define STRIP_LED_AMOUNT 229 // 14 STEPS
// #define STRIP_LED_AMOUNT 244 // 15 STEPS
// #define STRIP_LED_AMOUNT 261 // 10 STEPS
#define STRIP_LED_AMOUNT 318 // 10 STEPS
// #define STRIP_LED_AMOUNT 270  // количество чипов WS2811/WS2812 на всех ступеньках. Для WS2811 кол-во чипов = кол-во светодиодов / 3
#define STEP_AMOUNT 18       // количество ступенек

// описание всех ступенек с возможностью подсветки ЛЮБЫХ ступенек в ночном режиме
Step steps[STEP_AMOUNT] = { 
{ 17, 0b00000000 },   // первая ступенька 16 чипов, 0b0100100100100100 - каждый третий чип активен в ночном режиме
{ 17, 0b00000000 },   // вторая ступенька 16 чипов, 0b0000000000000000 - не активен в ночном режиме
{ 17, 0b00000000 },   // 3
{ 17, 0b00000100 },   // 4
{ 17, 0b00000000 },   // 5
{ 17, 0b00000000 },   // 6
{ 17, 0b00000000 },   // 7
{ 20, 0b00000000 },   // 8
{ 20, 0b00000000 },   // 9
{ 17, 0b00000000 },   // 10
{ 20, 0b00000000 },   // 11
{ 20, 0b00000000 },   // 12
{ 17, 0b00000000 },   // 13
{ 17, 0b00000000 },   // 14
{ 17, 0b00000000 },   // 15
{ 17, 0b01001001 },   // 16
{ 17, 0b01001001 },   // 17
{ 17, 0b01001001 }    // 18
};

// Step steps[STEP_AMOUNT] = { 
// { 16, 0b0100100100100100 },   // первая ступенька 16 чипов, 0b0100100100100100 - каждый третий чип активен в ночном режиме
// { 16, 0b0000000000000000 },   // вторая ступенька 16 чипов, 0b0000000000000000 - не активен в ночном режиме
// { 16, 0b0000000000000000 },   // 3
// { 16, 0b0000000000000000 },   // 4
// { 16, 0b0000000000000000 },   // 5
// { 16, 0b0000000000000000 },   // 6
// { 16, 0b0000000000000000 },   // 7
// { 16, 0b0000000000000000 },   // 8
// { 16, 0b0000000000000000 },   // 9
// { 16, 0b0000000000000000 },   // 10
// { 16, 0b0000000000000000 },   // 11
// { 16, 0b0000000000000000 },   // 12
// { 16, 0b0000000000000000 },   // 13
// { 16, 0b0000000000000000 },   // 14
// { 16, 0b0000000000000000 },   // 15
// { 16, 0b0100100100100100 }    // 16
// };

#define AUTO_BRIGHT 0     // автояркость вкл(1)/выкл(0) (с фоторезистором)
#define CUSTOM_BRIGHT 25  // ручная яркость

#define FADR_SPEED 400         // скорость переключения с одной ступеньки на другую, меньше - быстрее
#define START_EFFECT FIRE   // режим при старте COLOR, RAINBOW, FIRE
#define ROTATE_EFFECTS 1      // вкл(1)/выкл(0) - автосмена эффектов
#define TIMEOUT 15            // секунд, таймаут выключения ступенек после срабатывания одного из датчиков движения

#define NIGHT_LIGHT_COLOR mCOLOR(WHITE)  // по умолчанию белый
#define NIGHT_LIGHT_BRIGHT 50  // 0 - 255 яркость ночной подсветки
#define NIGHT_PHOTO_MAX 500   // максимальное значение фоторезистора для отключения подсветки, при освещении выше этого подсветка полностью отключается

// #define RAILING 0      // вкл(1)/выкл(0) - подсветка перил
// #define RAILING_LED_AMOUNT 75    // количество чипов WS2811/WS2812 на ленте перил

#define BUTTON  0      // вкл(1)/выкл(0) - сенсорная кнопка переключения эффектов

// пины
// если перепутаны сенсоры - можно поменять их местами в коде! Вот тут
#define SENSOR_START 3   // пин датчика движения
#define SENSOR_END 2     // пин датчика движения
#define STRIP_PIN 12     // пин ленты ступенек
// #define RAILING_PIN 11   // пин ленты перил
#define PHOTO_PIN A0     // пин фоторезистора
#define BUTTON_PIN 6     // пин сенсорной кнопки переключения эффектов

#define ORDER_GRB   // порядок цветов ORDER_GRB / ORDER_RGB / ORDER_BRG
#define COLOR_DEBTH 2   // цветовая глубина: 1, 2, 3 (в байтах)

// для разработчиков
#include <microLED.h>
#include <FastLED.h> // ФЛ для функции Noise

// #if (BUTTON == 1)
// #include <GyverButton.h>
// #endif

// ==== удобные макросы ====
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)
#define FOR_k(from, to) for(int k = (from); k < (to); k++)
#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr = millis();\
  if (flag)
//===========================

// int railingSegmentLength = RAILING_LED_AMOUNT / STEP_AMOUNT;   // количество чипов WS2811/WS2812 на сегмент ленты перил

LEDdata stripLEDs[STRIP_LED_AMOUNT];  // буфер ленты ступенек
microLED strip(stripLEDs, STRIP_LED_AMOUNT, STRIP_PIN);  // объект лента (НЕ МАТРИЦА) из-за разного количества диодов на ступеньку!

// #if (RAILING == 1)
// LEDdata railingLEDs[RAILING_LED_AMOUNT];  // буфер ленты перил
// microLED railing(railingLEDs, RAILING_LED_AMOUNT, RAILING_PIN);  // объект лента
// #endif

int effSpeed;
int8_t effectDirection;
byte curBright = CUSTOM_BRIGHT;
enum {COLOR, RAINBOW, FIRE, EFFECTS_AMOUNT} curEffect = START_EFFECT;
byte effectCounter;
uint32_t timeoutCounter;
bool systemIdleState;
bool systemOffState;
int steps_start[STEP_AMOUNT];

struct PirSensor {
  int8_t effectDirection;
  int8_t pin;
  bool lastState;
};

PirSensor startPirSensor = { 1, SENSOR_START, false};
PirSensor endPirSensor = { -1, SENSOR_END, false};

CRGBPalette16 firePalette;

int8_t minStepLength = steps[0].led_amount;

// #if (BUTTON == 1)
// GButton button(BUTTON_PIN);
// #endif

void setup() {
  Serial.begin(9600);
  setBrightness(curBright);    // яркость (0-255)
  clear();
  show();  
  
// #if (BUTTON == 1)
//   button.setType(HIGH_PULL);
//   button.setDirection(NORM_OPEN);
//   button.setDebounce(100);     // настройка антидребезга (по умолчанию 80 мс)
//   button.setTimeout(700);      // настройка таймаута на удержание (по умолчанию 500 мс)
//   button.setClickTimeout(600); // настройка таймаута между кликами (по умолчанию 300 мс)
// #endif

  firePalette = CRGBPalette16(
                  getFireColor(0 * 16),
                  getFireColor(1 * 16),
                  getFireColor(2 * 16),
                  getFireColor(3 * 16),
                  getFireColor(4 * 16),
                  getFireColor(5 * 16),
                  getFireColor(6 * 16),
                  getFireColor(7 * 16),
                  getFireColor(8 * 16),
                  getFireColor(9 * 16),
                  getFireColor(10 * 16),
                  getFireColor(11 * 16),
                  getFireColor(12 * 16),
                  getFireColor(13 * 16),
                  getFireColor(14 * 16),
                  getFireColor(15 * 16)
                );
  // определяем минимальную ширину ступеньки для корректной работы эффекта огня
  steps_start[0] = 0;
  FOR_i(1, STEP_AMOUNT) {
    if (steps[i].led_amount < minStepLength) {
      minStepLength = steps[i].led_amount;
    }
    steps_start[i] = steps_start[i-1] + steps[i-1].led_amount; // вычисляем стартовые позиции каждой ступеньки
  }
  delay(100);
  clear();
  show();
}

void loop() {
  // effectFlow();
  // handleTimeout();
  // handleButton();
  handlePirSensor(&startPirSensor);
  handlePirSensor(&endPirSensor);
  if (systemIdleState || systemOffState) {
    handlePhotoResistor();
    // handleNightLight();
    delay(50);
  } else {
    effectFlow();
    handleTimeout();
  }
}

// void handleButton() {
// #if (BUTTON == 1)
//   button.tick();
//   if (button.isClick() || button.isHolded())
//   {
//     curEffect = ++effectCounter % EFFECTS_AMOUNT;
//   }
// #endif
// }

void handlePhotoResistor() {
#if (AUTO_BRIGHT == 1)
  EVERY_MS(3000) {            // каждые 3 сек
    int photo = analogRead(PHOTO_PIN);
    Serial.print("Photo resistor ");
    Serial.println(photo);
    systemOffState = photo > NIGHT_PHOTO_MAX;
    curBright = systemOffState ? 0 : map(photo, 30, 800, 10, 200);
    setBrightness(curBright);
  }
#endif
}

// void handleNightLight() {
//   EVERY_MS(60000) {
//     nightLight();
//   }
// }

// void nightLight() {
//   if (systemOffState) {
//     Serial.println("System OFF ");
//     clear();
//     show();
//     return;
//   }
//   animatedSwitchOff(NIGHT_LIGHT_BRIGHT);
//   clear();
//   FOR_i(0, STEP_AMOUNT) {
//     // циклически сдвигаем маску, чтобы диоды не выгорали
//     if (steps[i].night_mode_bitmask) {
//       steps[i].night_mode_bitmask = (uint16_t) steps[i].night_mode_bitmask >> 1 | steps[i].night_mode_bitmask << 15;
//       fillStepWithBitMask(i, NIGHT_LIGHT_COLOR, steps[i].night_mode_bitmask);
//     }
//   }
//   animatedSwitchOn(NIGHT_LIGHT_BRIGHT);
// }

void handleTimeout() {
  if (millis() - timeoutCounter >= (TIMEOUT * 1000L)) {
    systemIdleState = true;
    if (effectDirection == 1) {
      stepFader(0, 1);
    } else {
      stepFader(1, 1);
    }
    // nightLight();
  }
}

void handlePirSensor(PirSensor *sensor) {
  if (systemOffState) return;

  int newState = digitalRead(sensor->pin);
  if (newState && !sensor->lastState) {
    Serial.print("PIR sensor ");
    Serial.println(sensor->pin);
    timeoutCounter = millis(); // при срабатывании датчика устанавливаем заново timeout
    if (systemIdleState) {
      effectDirection = sensor->effectDirection;
      if (ROTATE_EFFECTS) {
        curEffect = ++effectCounter % EFFECTS_AMOUNT;
      }
      stepFader(effectDirection == 1 ? 0 : 1,  0);
      systemIdleState = false;
    }
  }
  sensor->lastState = newState;
}

// крутилка эффектов в режиме активной работы
void effectFlow() {
  static uint32_t tmr;
  if (millis() - tmr >= effSpeed) {
    tmr = millis();
    switch (curEffect) {
      case COLOR: staticColor(effectDirection, 0, STEP_AMOUNT); break;
      case RAINBOW: rainbowStripes(-effectDirection, 0, STEP_AMOUNT); break; // rainbowStripes - приёмный
      case FIRE: fireStairs(effectDirection, 0, 0); break;
    }
    show();
  }
}
