#!/usr/bin/env ruby

def arredy_has(lines)
  for line in lines do
    if line.match? "use strict;" then
      return true
    end
  end

  false
end

def insert_use_strict(file)
  lines = file.readlines
  strict = "use strict;"

  if lines.length == 0; lines.insert(0, strict)
  elsif not arredy_has lines
    lines.each_with_index { |line, index|
      if not line.match? '#' then
        lines.insert(index, strict)
        break
      elsif index == lines.length - 1 then
        lines.insert(index + 1, strict)
        break
      end
    }
  end

  file.reopen(file, 'w')
  file.puts(lines)
  file.clone
end

def insert_in_files_of_dir(dirname)
  Dir.foreach(dirname) { |child|
    if child.match? /.+\.pl/ then
      insert_use_strict(File.open(dirname + "/" + child))
    end
  }
end

insert_in_files_of_dir("test")
