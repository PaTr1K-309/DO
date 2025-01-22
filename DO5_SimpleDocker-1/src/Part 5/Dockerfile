FROM nginx
WORKDIR /home/
COPY nginx.conf ../etc/nginx/nginx.conf
COPY server.c .
COPY run.sh .
RUN chmod +x run.sh \ 
&& rm -rf /var/lib/apt/lists/* \
&& apt -y update \ 
&& apt install -y gcc libfcgi-dev spawn-fcgi \
&& apt-get clean 
RUN useradd -ms /bin/bash user \
    && chown -R user:user /home \
    && chown -R user:user /etc/nginx/nginx.conf \
    && chown -R user:user /var/cache \
    && chmod u-s /usr/bin/mount /usr/bin/newgrp /usr/bin/umount /usr/bin/chfn /usr/bin/su /usr/bin/gpasswd /usr/bin/passwd /usr/bin/chsh \
    && chmod g-s /usr/bin/chage /usr/bin/wall /usr/sbin/unix_chkpwd /usr/bin/expiry \
    && touch /var/run/nginx.pid \
    && chown -R user:user /usr/bin \
    && chown -R user:user /usr/sbin \
    && chown -R user:user /var \
    && chmod 755 /var \ 
    && chown -R user:user /run 
   # && chown -R user:user /var/cache/nginx/client_temp 
USER user
ENTRYPOINT ["./run.sh"]