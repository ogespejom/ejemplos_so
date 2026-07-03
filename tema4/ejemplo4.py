import psutil
import os

def auditoria_memoria():
    virtual_mem = psutil.virtual_memory()
    swap = psutil.swap_memory()

    print("Diagnóstico de memoria\n")
    print(f'RAM total: {virtual_mem.total / (1024**3):.2f} GB\n')
    print(f'RAM disponible: {virtual_mem.available / (1024**3):.2f} GB\n')
    print(f'Uso de memoria de intercambio: {swap.percent} %')
    #Proceso actual
    pid = psutil.Process(os.getpid());
    print(f'RSS (Resident Set Size) {pid.memory_info().rss / (1024**3)} MB\n')

if __name__ == "__main__":
    auditoria_memoria()