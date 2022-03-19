FROM node
LABEL maintainer aamirglb@gmail.com
RUN git clone -q https://github.com/docker-in-practice/todo.git
WORKDIR todo
RUN npm install > /dev/null
EXPOSE 8000
CMD ["npm", "start"]
