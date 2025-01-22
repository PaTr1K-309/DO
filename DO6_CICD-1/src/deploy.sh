#!/bin/bash

USER=joeylytl
HOST=172.24.116.8
REMOTE_PATH=/usr/local/bin
LOCAL_ARTIFACTS=src

echo "Start deploy!!"

if [[ ! -f "$LOCAL_ARTIFACTS/cat/s21_cat" || ! -f "$LOCAL_ARTIFACTS/grep/s21_grep" ]]; then
  echo "Ошибка: необходимые артифакты не найдены в $LOCAL_ARTIFACTS"
  exit 1;
fi

scp "$LOCAL_ARTIFACTS/cat/s21_cat" "$USER@$HOST:$REMOTE_PATH"
scp "$LOCAL_ARTIFACTS/grep/s21_grep" "$USER@$HOST:$REMOTE_PATH"

if [[ $? -ne 0 ]]; then
 echo "Ошибка при копировании файлов" 
 exit 1
fi

ssh "$USER@$HOST" "chmod +x $REMOTE_PATH/s21_cat && chmod +x $REMOTE_PATH/s21_grep && echo 'Программы успешно развернуты'"
