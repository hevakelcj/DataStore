DataStore
=========

It a store which can putin data in sequeue, and fetch data from it. If store is full, the oldest data will be remove to make more space to store new data. It can read data in random. 
hevakelcj@gmail.com

DataStore is a class which can store data in sequeue.
After store data in, we can get any one by readAt(index)
If space is full, the most age-old data will be remove to 
make more space for nearest data.

datastore.h  -- header file
datastore.cpp -- source file

main.cpp   -- usage demon
