echo 'Input path to the file (relative to the root directory):'
read path

if [ ! -f "$path" ]; then
  echo 'No such file! Error!'
  exit 1
fi

echo 'Input string to be replaced:'
read search_str

if [ -z "$search_str" ]; then
  echo 'String to be replaced must not be empty! Error!'
  exit 1
fi

echo 'Input replacement string:'
read replace_str

if [ -z "$replace_str" ]; then
  echo 'Replacement string is empty! Warning!'
fi

sed -i '' "s/$search_str/$replace_str/g" $path

if [ ! $? -eq 0 ]; then
  echo 'Sed returned bad code! Error!'
  exit 1
fi

log_date=$(date +"%Y-%m-%d %H:%M")
log="$path - $(wc -c $path | awk '{print $1}') - $log_date - $(shasum -a256 $path | awk '{print $1}') - sha256"

echo "Result log:"
echo $log
echo $log >> ./files.log
