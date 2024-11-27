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
  echo "-t        Muestra solo los procesos con una terminal especificada"
  echo "-e        Muestra los procesos en modo lista. Si no se especifica la salida estará en modo tabla"
  echo "-sm       Muestra los procesos en orden ascendente de su consumo de memoria.
          Si la salida está en modo tabla se ordenará por el total de la memoria consumida por las sesiones"
  echo "-sg       Muestra las sesiones en orden descendente por el número de grupos (No es compatible con -e ni -sm)"
  echo "-r        Invierte el orden de la salida"
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
ord_mem=0
ord_gru=0
reverse=0
leyendo_usu=0

while [ "$1" != "" ]; do
  case "$1" in
    "-h" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            ayuda_b=1
          else
            ayuda_b=1
          fi
      ;;
    "-z" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            pid0=1
          else
            pid0=1
          fi
      ;;
    "-u" ) usuario_b=1
          if [ $leyendo_usu -eq 1 ]; then
            error_exit "Error opción invalida. Utilize $0 -h para más información"
          fi
          leyendo_usu=1
          if [[ "$2" == -* || "$2" == "" ]]; then
            error_exit "Error usuario no especificado"
          fi
      ;;
    "-d" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            directorio_b=1
          else
            directorio_b=1
          fi
      shift
      if [[ "$1" != "" && "$1" != "-"* ]]; then
        directorio="$1"
        if ! [ -d "$1" ]; then
          error_exit "Error, directorio $1 no encontrado. Utilize $0 -h para más información"
        fi
      else
        error_exit "Error directorio no especificado"
      fi
      ;;
      "-t" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            terminal=1
          else
            terminal=1
          fi
      ;;
      "-e" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            modo_lista=1
          else
            modo_lista=1
          fi
      ;;
      "-sm" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            ord_mem=1
          else
            ord_mem=1
          fi
      ;;
      "-sg" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            ord_gru=1
          else
            ord_gru=1
          fi
      ;;
      "-r" ) if [ $leyendo_usu -eq 1 ]; then
            leyendo_usu=0
            reverse=1
          else
            reverse=1
          fi
      ;;
    * ) if [ $leyendo_usu -eq 1 ]; then
          usuarios[index_usuario]=$1
          index_usuario=$(( $index_usuario + 1 ))
          if ! [ $(grep -w "^$1" /etc/group) ]; then
            error_exit "Error, el usuario $1 no existe. Utilize $0 -h para más información"
          fi
        else
          error_exit "Error opción invalida. Utilize $0 -h para más información"
        fi
  esac 
  shift
done

# Mostrar ayuda
if [ $ayuda_b -eq 1 ]; then
  ayuda
fi

# Verificar que las opciones sean compatibles
if [ $modo_lista -eq 1 ] && [ $ord_gru -eq 1 ] || [ $ord_mem -eq 1 ] && [ $ord_gru -eq 1 ]; then
  error_exit "Error opciones incompatibles. Utilize $0 -h para más información"
fi

# Modo Lista
if [ $modo_lista -eq 1 ]; then
printf "%-10s %-10s %-10s %-20s %-10s %-10s %-10s" "SID" "PGID" "PID" "USER" "TTY" "%MEM" "CMD"
# -z
if [ $pid0 -eq 0 ]; then
  proc="$(echo "$proc" | awk '$1 > 0 {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
else
  proc="$(echo "$proc" | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -u
if [ $usuario_b -eq 1 ]; then
  aux=""
  for i in ${usuarios[*]}; do
    aux="$aux $(echo "$proc" | grep $i | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
  done
  proc="$aux"
else
  proc="$(echo "$proc" | awk -v user=$USER '$4 == user {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -d
if [ $directorio_b -eq 1 ]; then
  aux=""
  for i in "$(procesos_dir $directorio)"; do
    aux="$aux $(echo "$proc" | grep "$i" | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"  
  done
  proc="$aux"
fi

# -t
if [ $terminal -eq 1 ]; then
  proc="$(echo "$proc" | awk '$5 != "?" {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
fi


# Opciones de ordenación
# Por memoria
if [ $ord_mem -eq 1 ]; then
  if [ $reverse -eq 1 ]; then
    proc="$(echo "$proc" | tr -s '  ' ' ' | awk 'NR > 1 {print}' | sort -k 6 -r | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
  else
    proc="$(echo "$proc" | tr -s '  ' ' ' | sort -k 6 | awk ' NR > 1 {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
  fi
# Por usuario
else
  if [ $reverse -eq 1 ]; then
    proc="$(echo "$proc" | tr -s '  ' ' ' | awk 'NR > 1 {print}' | sort -k 4 -r | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
  else
    proc="$(echo "$proc" | tr -s '  ' ' ' | sort -k 4 | awk 'NR > 1 {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
  fi
fi

# Salida
echo "$proc"


# Modo tabla
else
# -z
if [ $pid0 -eq 0 ]; then
  proc="$(echo "$proc" | awk '$1 > 0 {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
else
  proc="$(echo "$proc" | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -u
if [ $usuario_b -eq 1 ]; then
  aux=""
  for i in ${usuarios[*]}; do
    aux="$aux $(echo "$proc" | grep $i | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
  done
  proc="$aux"
else
  proc="$(echo "$proc" | awk -v user=$USER '$4 == user {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
fi

# -d
if [ $directorio_b -eq 1 ]; then
  aux=""
  for i in "$(procesos_dir $directorio)"; do
    aux="$aux $(echo "$proc" | grep "$i" | awk '{printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"  
  done
  proc="$aux"
fi

# -t
if [ $terminal -eq 1 ]; then
  proc="$(echo "$proc" | awk '$5 != "?" {printf "\n%-10s %-10s %-10s %-20s %-10s %-10s %-10s", $1, $2, $3, $4, $5, $6, $7}')"
fi

printf "%-10s %-10s %-20s %-20s %-20s %-20s %-20s" "SID" "nPGID" "%MEM TOTAL" "PID LIDER" "USER LIDER" "TTY LIDER" "CMD LIDER"
aux=""
n_PGID=""
pid_lider=""
por_mem=$(awk ' BEGIN {print 0.0}')
usu_lider=""
tty_lider=""
cmd_lider=""
for sid in $(echo "$proc" | awk '{print $1}' | sort | uniq); do
  n_PGID=$(procesos | awk -v sid="$sid" '$1 == sid {print $1}' | wc -l)
  por_mem=$(procesos | LC_ALL=C awk -v sid="$sid" '$1 == sid {sum += $6} END {print sum}')
  pid_lider="$(echo "$proc" | awk '{print $3}' | sort | grep -w $sid | uniq)"
  if [ "$pid_lider" == "" ]; then
  pid_lider="?"
  fi
  if [ "$pid_lider" != "?" ]; then
      usu_lider=$(echo "$proc" | awk -v pid="$pid_lider" '$3 == pid {print $4}')
      tty_lider=$(echo "$proc" | awk -v pid="$pid_lider" '$3 == pid {print $5}')
      cmd_lider=$(echo "$proc" | awk -v pid="$pid_lider" '$3 == pid {print $7}')
  fi
  if [ "$usu_lider" == "" ]; then
    usu_lider="?"
  fi
  if [ "$tty_lider" == "" ]; then
    tty_lider="?"
  fi
  if [ "$cmd_lider" == "" ]; then
    cmd_lider="?"
  fi
  aux="$aux $(printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s" "$sid" "$n_PGID" $por_mem "$pid_lider" "$usu_lider" "$tty_lider" "$cmd_lider")"
  usu_lider=""
  tty_lider=""
  cmd_lider=""
  por_mem=$(awk ' BEGIN {print 0.0}')
done
proc="$aux"

# Opciones de ordenación
# Por memoria
if [ $ord_mem -eq 1 ]; then
  if [ $reverse -eq 1 ]; then
    proc="$(echo "$proc" | tr -s '  ' ' ' | awk 'NR > 1 {print}' | sort -k 3 -r | awk '{printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s", $1, $2, $3, $4, $5, $6, $7}')"
  else
    proc="$(echo "$proc" | tr -s '  ' ' ' | sort -k 3 | awk ' NR > 1 {printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s", $1, $2, $3, $4, $5, $6, $7}')"
  fi
# Por número de grupos
elif [ $ord_gru -eq 1 ]; then
  if [ $reverse -eq 1 ]; then
    proc="$(echo "$proc" | tr -s '  ' ' ' | awk 'NR > 1 {print}' | sort -k 2 -r | awk '{printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s", $1, $2, $3, $4, $5, $6, $7}')"
  else
    proc="$(echo "$proc" | tr -s '  ' ' ' | sort -k 2 | awk ' NR > 1 {printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s", $1, $2, $3, $4, $5, $6, $7}')"
  fi
# Por usuario
else
  if [ $reverse -eq 1 ]; then
    proc="$(echo "$proc" | tr -s '  ' ' ' | awk 'NR > 1 {print}' | sort -k 5 -r | awk '{printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s", $1, $2, $3, $4, $5, $6, $7}')"
  else
    proc="$(echo "$proc" | tr -s '  ' ' ' | sort -k 5 | awk 'NR > 1 {printf "\n%-10s %-10s %-20.1f %-20s %-20s %-20s %-20s", $1, $2, $3, $4, $5, $6, $7}')"
  fi
fi

#salida
echo "$proc"
fi

exit 0