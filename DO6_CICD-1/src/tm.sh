#!/bin/bash

USER_ID="1374233918"
BOT-TOKEN="8022489742:AAG9D4DEsBEBboixSbeV6I1pWzkblz85Dqg"
TIME="5"
URL="https://api.telegram.org/bot8022489742:AAG9D4DEsBEBboixSbeV6I1pWzkblz85Dqg/sendMessage"
TEXT="$CI_JOB_NAME: $CI_JOB_STATUS"

curl -s --max-time $TIME -d "chat_id=$USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
