#!/bin/bash

procesos() {
ps -eo sid,pgid,pid,user,tty,%mem,cmd --sort user --noheader | awk 'BEGIN {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "SID", "PGID", "PID", "USER", "TTY", "%MEM", "CMD"} $1 > 0 {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}'
}

ayuda() {
  echo "Modo de ejecución: $0 [opciones]"
  echo "Lista de opciones:"
  echo "-h        Muestra la ayuda del comando"
  echo "-u USER   Muestra solo los procesos del usuario especificado"
  echo "-d DIR    Muestra solo los procesos que tengan abiertos archivos en el directorio especificado por dir"
  exit 0
}

pid0=0
procesos_pid0() {
ps -eo sid,pgid,pid,user,tty,%mem,cmd --sort user --noheader | awk 'BEGIN {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "SID", "PGID", "PID", "USER", "TTY", "%MEM", "CMD"} {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}'
}

usuario_b=0
usuario=
procesos_usuario() {
ps -o sid,pgid,pid,user,tty,%mem,cmd --sort user --noheader -u $1 | awk 'BEGIN {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "SID", "PGID", "PID", "USER", "TTY", "%MEM", "CMD"} $1 > 0 {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}'
}

procesos_usuario_pid0() {
  ps -o sid,pgid,pid,user,tty,%mem,cmd --sort user --noheader -u $1 | awk 'BEGIN {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "SID", "PGID", "PID", "USER", "TTY", "%MEM", "CMD"} {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}'
}

directorio_b=0
directorio=
procesos_dir() {
  lsof +d $directorio | awk '{printf "%-10s %-10s %-15s %-10s %-10s %-10s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7, $8, $9}'
}

procesos_dir_usr(){
  lsof +d $2 | awk -v user=$1 ' $3 == user {printf "%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7, $8, $9}'
}

if [ $# -eq 0 ]; then
  procesos
  exit 0
fi

while [ "$1" != "" ]; do
  case "$1" in
    "-h" ) ayuda
      ;;
    "-z" ) pid0=1
      ;;
    "-u" ) usuario_b=1
      shift
      if [ "$1" != "" ]; then
        usuario="$1"
      else
        echo "Error usuario no especificado"
        exit 1
      fi
      ;;
    "-d" ) directorio_b=1
      shift
      if [ "$1" != "" ]; then
        directorio="$1"
      else
        echo "Error directorio no especificado"
        exit 1
      fi
      ;;
    * ) echo "Error opción invalida"
        echo "Utilize $0 -h para más información" 
        exit 1
  esac 
  shift
done

if [ $directorio_b -eq 1 -a $usuario_b -eq 1 ]; then
  procesos_dir_usr $usuario $directorio
  exit 0
elif [ $directorio_b -eq 1 ]; then
  procesos_dir $directorio
  exit 0
elif [ $pid0 -eq 1 -a $usuario_b -eq 1 ]; then
  procesos_usuario_pid0 $usuario
  exit 0
elif [ $pid0 -eq 1 ]; then
  procesos_pid0
  exit 0
elif [ $usuario_b -eq 1 ]; then
  procesos_usuario $usuario
  exit 0
fi

