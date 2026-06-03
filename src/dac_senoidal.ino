const int pinD0 = A5; // LSB -> Conectar a la resistencia de 2k más lejana
const int pinD1 = A4;
const int pinD2 = A3; // MSB -> Conectar a la resistencia de 2k más cercana al op-amp

// --- PIN DE RELOJ ---
const int clkPin = 6; 

// --- PIN DEL POTENCIÓMETRO ---
const int pinPoti = A1; 

// Tu onda senoidal original de 3 bits (valores del 0 al 7)
byte ondaSenoidal[16] = {4, 5, 6, 7, 7, 7, 6, 5, 3, 2, 1, 0, 0, 0, 1, 2};

// --- VARIABLES DE TIEMPO PARA SEPARAR ONDA Y RELOJ ---
unsigned long tiempoAnteriorOnda = 0;
unsigned long tiempoAnteriorReloj = 0;
unsigned long tiempoAnteriorPoti = 0;

int indiceOnda = 0;
unsigned long velocidadReloj = 1000; 

// Velocidad fija de la onda (cambia cada 2000 microsegundos = 2 milisegundos)
const unsigned long VELOCIDAD_FIJA_ONDA = 2000; 

void setup() {
  pinMode(pinD0, OUTPUT);
  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(clkPin, OUTPUT);
  
  digitalWrite(clkPin, LOW);
}

// ESTA FUNCIÓN SOLO PONE LOS DATOS EN LOS 3 PINES
void escribirDatos(byte valor) {
  digitalWrite(pinD0, bitRead(valor, 0));
  digitalWrite(pinD1, bitRead(valor, 1));
  digitalWrite(pinD2, bitRead(valor, 2));
}

void loop() {
  unsigned long tiempoActual = micros();

  // 1. LEER EL POTENCIÓMETRO (Solo lo leemos cada 50ms)
  if (tiempoActual - tiempoAnteriorPoti >= 50000) {
    tiempoAnteriorPoti = tiempoActual;
    int valorPoti = analogRead(pinPoti);
    
    // Mapeamos a microsegundos (100us es muestreo rápido, 30000us es submuestreo lento)
    velocidadReloj = map(valorPoti, 0, 1023, 100, 30000); 
  }

  // 2. ACTUALIZAR LOS DATOS DE LA ONDA (A velocidad constante e intocable)
  if (tiempoActual - tiempoAnteriorOnda >= VELOCIDAD_FIJA_ONDA) {
    tiempoAnteriorOnda = tiempoActual;
    
    escribirDatos(ondaSenoidal[indiceOnda]);
    
    indiceOnda++;
    if (indiceOnda >= 16) indiceOnda = 0;
  }

  // 3. DISPARAR EL RELOJ DEL ZOH (A la velocidad del potenciómetro)
  if (tiempoActual - tiempoAnteriorReloj >= velocidadReloj) {
    tiempoAnteriorReloj = tiempoActual;
    
    // Aquí es donde el Flip-Flop "atrapa" lo que sea que esté en los pines en ese instante
    digitalWrite(clkPin, HIGH);
    delayMicroseconds(2); 
    digitalWrite(clkPin, LOW);
  }
}
