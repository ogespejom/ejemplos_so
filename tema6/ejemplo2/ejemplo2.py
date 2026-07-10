import mmap
import os
import time

FILE_NAME = "disco_simulado_grande.bin"
TAMANO_MB = 200

print(f"Preparando entorno: Creando archivo de {TAMANO_MB} MB... (espera un momento)")
with open(FILE_NAME, "wb") as f:
    # Escribimos 200 MB de datos al disco
    f.write(b"X" * 1024 * 1024 * TAMANO_MB)

print("\n--- Escenario 1: E/S Tradicional (Copia a través del CPU) ---")
inicio_read = time.perf_counter()

with open(FILE_NAME, "rb") as f:
    # f.read() obliga al CPU a copiar byte por byte (200 Millones de bytes) 
    # desde la memoria del kernel hacia la variable 'datos' en el espacio de usuario.
    datos = f.read() 
    
fin_read = time.perf_counter()
tiempo_read = fin_read - inicio_read
print(f"Tiempo de E/S Tradicional: {tiempo_read:.5f} segundos")


print("\n--- Escenario 2: E/S con mmap y DMA (Zero-Copy) ---")
inicio_mmap = time.perf_counter()

with open(FILE_NAME, "r+b") as f:
    # mmap pide al SO crear los punteros a memoria. 
    # El hardware (DMA) maneja el movimiento de bloques del disco a la RAM.
    # El CPU NO copia los datos al espacio de usuario, solo accede a ellos directamente.
    memoria_mapeada = mmap.mmap(f.fileno(), 0)
    
    # Hacemos una lectura para comprobar que el archivo está ahí
    dato_prueba = memoria_mapeada[0:10] 
    memoria_mapeada.close()
    
fin_mmap = time.perf_counter()
tiempo_mmap = fin_mmap - inicio_mmap
print(f"Tiempo con mmap (DMA):     {tiempo_mmap:.5f} segundos")

# Conclusión matemática para la clase
if tiempo_mmap > 0:
    aceleracion = tiempo_read / tiempo_mmap
    print(f"\n[!] Conclusión: ¡El método mmap fue aprox. {aceleracion:.1f} veces más rápido!")

# Limpiamos el archivo
os.remove(FILE_NAME)