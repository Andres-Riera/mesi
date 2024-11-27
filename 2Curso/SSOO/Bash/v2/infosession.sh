#!/bin/bash

PROGNAME=$(basename $0)

procesos() {
ps -eo sid,pgid,pid,tty,%mem,cmd,user --sort user --noheader | awk '{printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $7, $4, $5, $6}'
}
proc="$(procesos)"

ayuda_b=0
ayuda() {
  echo "Modo de ejecución: $0 [opciones]"
  echo "Lista de opciones:"
  echo "-h        Muestra la ayuda del comando"
  echo "-z        Muestra todos los procesos incluidos los que tengan un SID de 0"
  echo "-u USER   Muestra solo los procesos de los usuarios especificados"
  echo "-d DIR    Muestra solo los procesos que tengan abiertos archivos en el directorio especificado por dir"
  exit 0
}

error_exit() {
  echo "${PROGNAME}: ${1:-"Error desconocido"}" 1>&2
  exit 1
}

pid0=0

terminal=0

usuario_b=0
usuarios=()
index_usuario=$(( 0 ))

directorio_b=0
directorio=
procesos_dir() {
  lsof +d "$directorio" | awk 'NR > 1 {print $2}'
}

modo_lista=0
modificacion=0
archivo=
while [ "$1" != "" ]; do
  case "$1" in
    "-h" ) ayuda_b=1
      ;;
    "-z" ) pid0=1
      ;;
    "-u" ) usuario_b=1
          shift
          if [ "$1" != "" ]; then
            usuarios[index_usuario]=$1
            index_usuario=$(( $index_usuario + 1))
            while [ "$2" != "" ] && [[ "$2" != -* ]]; 

            do
              shift
              usuarios[index_usuario]=$1
              index_usuario=$(( $index_usuario + 1))
            done
          else
              error_exit "Error usuario no especificado"
          fi
      ;;
    "-d" ) directorio_b=1
      shift
      if [ "$1" != "" ]; then
        directorio="$1"
      else
        error_exit "Error directorio no especificado"
      fi
      ;;
      "-t" ) terminal=1
      ;;
      "-e" ) modo_lista=1
      ;;
      "-f" ) modificacion=1
      shift
      if [ "$1" != "" ]; then
        archivo="$1"
      else
        error_exit "Error archivo no especificado"
      fi
      ;;
    * ) error_exit "Error opción invalida. Utilize $0 -h para más información"
  esac 
  shift
done


if [ $ayuda_b -eq 1 ]; then
  ayuda
fi

# Modo Lista
if [ $modo_lista -eq 1 ]; then
printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n" "SID" "PGID" "PID" "USER" "TTY" "%MEM" "CMD"
# -z
if [ $pid0 -eq 0 ]; then
  proc="$(echo "$proc" | awk '$1 > 0 {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
else
  proc="$(echo "$proc" | awk '{printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -u
if [ $usuario_b -eq 1 ]; then
  aux=""
  for i in ${usuarios[*]}; do
    aux="$aux$(echo "$proc" | awk -v user_awk="$i" '$4 == user_awk {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
  done
  proc=$aux
else
  proc="$(echo "$proc" | awk -v user=$USER '$4 == user {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -d
if [ $directorio_b -eq 1 ]; then
  procesos_dir "$directorio" > archivo_temporal_directorios.txt
  echo "$proc" > archivo_temporal_procesos.txt
  proc=$(grep -f archivo_temporal_directorios.txt archivo_temporal_procesos.txt | awk '{printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')
  rm -f archivo_temporal_procesos.txt
  rm -f archivo_temporal_directorios.txt
fi

# -t
if [ $terminal -eq 1 ]; then
  proc="$(echo "$proc" | awk '$5 != "?" {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
fi

echo "$proc"
# -f
if [ $modificacion -eq 1 ]; then
  if [ $(echo "$proc" | wc -l) -gt 5 ]; then
    cat $archivo
  fi
fi
exit 0




# Modo tabla
else
# -z
if [ $pid0 -eq 0 ]; then
  proc="$(echo "$proc" | awk '$1 > 0 {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
else
  proc="$(echo "$proc" | awk '{printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -u
if [ $usuario_b -eq 1 ]; then
  aux=""
  for i in ${usuarios[*]}; do
    aux="$aux$(echo "$proc" | awk -v user_awk="$i" '$4 == user_awk {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
  done
  proc=$aux
else
  proc="$(echo "$proc" | awk -v user=$USER '$4 == user {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -d
if [ $directorio_b -eq 1 ]; then
  procesos_dir "$directorio" > archivo_temporal_directorios.txt
  echo "$proc" > archivo_temporal_procesos.txt
  proc=$(grep -f archivo_temporal_directorios.txt archivo_temporal_procesos.txt | awk '{printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')
  rm -f archivo_temporal_procesos.txt
  rm -f archivo_temporal_directorios.txt
fi

# -t
if [ $terminal -eq 1 ]; then
  proc="$(echo "$proc" | awk '$5 != "?" {printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')"
fi

proc_list=$(echo "$proc" | awk '{printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s\n", $1, $2, $3, $4, $5, $6, $7}')
printf "%-10s %-10s %-20s %-20s %-20s %-20s\n" "SID" "nPGID" "PID LIDER" "USER LIDER" "TTY LIDER" "CMD LIDER"
for sid in $(echo "$proc_list" | awk '{print $1}' | sort | uniq); do
    n_PGID="$(echo "$proc_list" | awk '{print $1, $3}' | grep $sid | wc -l)"
    pid_lider="$sid"
    usu_lider="$(echo "$proc_list" | awk '{print $3, $4}' | grep $pid_lider | awk '{print $2}')"
    tty_lider="$(echo "$proc_list" | awk '{print $3, $5}' | grep $pid_lider | awk '{print $2}')"
    cmd_lider="$(echo "$proc_list" | awk '{print $3, $7}' | grep $pid_lider | awk '{print $2}')"
    if [ "$usu_lider" == "" ]; then
      usu_lider="?"
    fi
    if [ "$tty_lider" == "" ]; then
      tty_lider="?"
    fi
    if [ "$cmd_lider" == "" ]; then
      cmd_lider="?"
    fi
    printf "%-10s %-10s %-20s %-20s %-20s %-20s\n" "$sid" "$n_PGID" "$pid_lider" "$usu_lider" "$tty_lider" "$cmd_lider"
done
# -f
if [ $modificacion -eq 1 ]; then
  if [ $(echo "$proc_list" | wc -l) -gt 5 ]; then
    cat $archivo
  fi
fi
exit 0

fi