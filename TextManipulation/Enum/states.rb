def gen_sample()
  open("input", "w") { |fp|
    printf(fp, "input\n")

    for v in (1..100) do
      printf(fp, "state_#{v}\n")
    end

    printf(fp, "EOF\n")
  }
end

def gen_dot_h(lines)
  name, states = lines[0], lines[1..]
  fp = open("#{name}.h", "w")

  printf(fp, "extern const char* #{name.upcase}_names[];\n")
  printf(fp, "typedef enum {\n")
  states.each { |state| printf(fp, "    #{state},\n") }
  printf(fp, "} #{name.upcase};\n")
  
end


def gen_dot_c(lines)
  name, states = lines[0], lines[1..]
  fp = open("#{name}.c", "w")
  
  printf(fp, "const char* #{name.upcase}_names[];\n")
  states.each { |state| printf(fp, "    \"#{state}\",\n") }
  printf(fp, "};\n")
end

def main
  if ARGV[0] == "gen" then
    gen_sample()
    exit()
  end

  line = ""
  lines = Array.new()

  print("Write EOF to terminate\n")
  while line != "EOF" do
    line = gets.chomp()
    lines << line
  end

  gen_dot_h lines[0..-2]
  gen_dot_c lines[0..-2]
end

main()
