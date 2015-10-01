# file: runme.rb

require 'example'

f = File.binread('face.jpg')
content = f.unpack('C*')
face_array = example.detectFaces(content, 3.0)