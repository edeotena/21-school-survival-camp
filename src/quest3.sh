mv door_management_fi door_management_files
cd door_management_files
mkdir door_logs
mkdir door_map
mkdir door_configuration
mv ./*.log door_logs
mv ./*.conf door_configuration
mv door_map_1.1 door_map
cd ..
chmod +x ai_door_control.sh
