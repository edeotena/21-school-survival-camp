if [ ! $# -eq 1 ]; then 
  echo 'Script must have 1 argument! Error!'
  exit 1
fi

if [ ! -f $1 ]; then
  echo "No file $1! Error!"
  exit 1
fi

repo="T02D02-0/"
files_counter=0
hash_counter=0
files_array=()
hash_array=()
cd ~/

while read -r line;
do
  words=(${line// - / })
  if [ ! -f "$repo${words[0]}" ] && [ ! -f "${words[0]}" ]; then
    continue
  fi
  if [[ ! "${files_array[*]}" =~ "${words[0]}" ]]; then
    files_array+=(${words[0]})
    hash_array+=(${words[4]})
    files_counter=$[files_counter + 1]
    hash_counter=$[hash_counter + 1]
  else 
    i=0
    size=${#files_array[@]}
    for ((i = 0 ; i < size; i++)); do
      if [[ "${files_array[$i]}" == "${words[0]}" ]]; then
        break
      fi
    done
    if [[ ${hash_array[$i]} != *${words[4]}* ]]; then
      hash_counter=$[hash_counter + 1]	
      hash_array[$i]+=" ${words[4]}"
    fi
  fi
done < $1
echo "$(wc -l $1 | awk '{print $1}') $files_counter $hash_counter"
