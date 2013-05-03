#!/usr/bin/ruby

require 'set'

numObjects = 0

objects = Set.new
staticObjects = Set.new

STDIN.each do |line|
  if /^\[LIBJ DEBUG\] construct: 0x(\w*)/ =~ line
    if objects.include?($1)
      raise "already constructed: " + $1
    else
      objects.add($1)
    end
  end

  if /^\[LIBJ DEBUG\] destruct:  0x(\w*)/ =~ line
    if !objects.include?($1)
#     warn "not constructed: " + $1
    else
      objects.delete($1)
    end
  end

  if /^\[LIBJ DEBUG\] static: (\w*) 0x(\w*)/ =~ line
    if staticObjects.include?($2)
      raise "already constructed: " + $2
    else
      staticObjects.add($2)
    end
  end

  if /^\[LIBJ DEBUG\] symbol: \[.*\] 0x(\w*)/ =~ line
    if staticObjects.include?($1)
      raise "already constructed: " + $1
    else
      staticObjects.add($1)
    end
  end

  if /^\[LIBJ DEBUG\] remaining objects: (\d*)/ =~ line
    numObjects = $1
    break;
  end
end

if objects.size != numObjects.to_i
  raise "remaining objects: not " + numObjects + " but " + objects.size.to_s;
end

leakedObjects = objects ^ staticObjects
if !leakedObjects.empty?
  raise "leaked objects: " + leakedObjects
end
