# Project 2 Load Balancer - Code Review

## ✅ Requirements Met

### Core Requirements
- ✅ **Multiple .cpp files**: All components properly separated
- ✅ **Request struct**: Contains ipIn, ipOut, processTime, jobType (now fixed to S/P)
- ✅ **WebServer class**: Processes requests, tracks completion
- ✅ **LoadBalancer class**: Manages queue and servers
- ✅ **Queue of requests**: std::queue<Request> implemented
- ✅ **User input**: Number of servers and clock cycles
- ✅ **Initial queue**: servers * 20 requests
- ✅ **Random new requests**: 30% chance per tick, 1-3 requests
- ✅ **Dynamic scaling**: 
  - Scale up when queue > 25 * servers ✅
  - Scale down when queue < 15 * servers ✅
  - Cooldown period (10 ticks) ✅
  - Only removes idle servers ✅
- ✅ **Firewall/IP blocker**: Blocks IPs from blocked_ranges.txt
- ✅ **Time tracking**: currentTick maintained
- ✅ **Logging**: Comprehensive log with tick-by-tick details

### Fixed Issues
- ✅ **Job types**: Changed from A-D to S (streaming) and P (processing) as required

## ⚠️ Issues Found & Status

### Critical Issues (FIXED)
1. ✅ **Job Type Mismatch**: 
   - **Was**: Generating 'A', 'B', 'C', 'D' 
   - **Fixed**: Now generates 'S' (streaming) or 'P' (processing)
   - **Location**: `src/RandomUtil.cpp::randomJobType()`

### Missing/Incomplete Items
1. ⚠️ **Doxygen Documentation**: 
   - No Doxyfile found
   - No HTML documentation generated
   - **Action Required**: Create Doxyfile and generate HTML docs
   - **Requirement**: 30% of grade

2. ⚠️ **Deliverable Log File**:
   - Need specific log: `run_10servers_10000cycles.log`
   - Current log is `simulation.log`
   - **Action Required**: Run with 10 servers, 10000 cycles and save to correct filename

3. ⚠️ **Optional Feature** (not required but mentioned):
   - Pre-sort jobs into streaming/processing and send to different server sets
   - Currently not implemented (optional)

## 📋 Code Quality Assessment

### Strengths
- ✅ Clean separation of concerns
- ✅ Proper use of classes and structs
- ✅ Good encapsulation (private/public)
- ✅ Header guards in all headers
- ✅ No `using namespace std` in headers (good practice)
- ✅ Modular design with RandomUtil
- ✅ Comprehensive logging
- ✅ Firewall integration working

### Architecture
- ✅ Request struct: Simple, effective
- ✅ WebServer: Handles request processing correctly
- ✅ LoadBalancer: Manages simulation loop properly
- ✅ Firewall: IP blocking functional
- ✅ RandomUtil: Centralized randomness (seedable)

## 🔍 Detailed Requirements Check

### Request Requirements
- ✅ IP in (string)
- ✅ IP out (string)  
- ✅ Time (integer) - processTime
- ✅ Job type S or P - **FIXED**

### Webserver Requirements
- ✅ Takes requests from Load Balancer
- ✅ Processes requests
- ✅ Asks for another (becomes idle when done)
- ✅ Dynamic scaling implemented
- ✅ Cooldown period respected

### Load Balancer Requirements
- ✅ Queue of requests
- ✅ Keeps track of time

### Program Structure
- ✅ Multiple .cpp files
- ✅ Main program sets up servers (user input)
- ✅ Time to run (user input)
- ✅ Full queue generation (servers * 20)
- ✅ Random new requests
- ✅ Exits when time ends

## 📝 Action Items Before Submission

### High Priority
1. **Create Doxygen Documentation** (30% of grade)
   ```bash
   # Install doxygen if needed
   # Create Doxyfile
   # Generate HTML docs
   # Upload to people.tamu.edu
   ```

2. **Generate Required Log File**
   ```bash
   echo -e "10\n10000" | ./load_balancer
   # Rename or copy logs/simulation.log to logs/run_10servers_10000cycles.log
   ```

3. **Verify Log Format**
   - Check that log contains all required information
   - Ensure scaling events are logged
   - Verify 10,000 ticks are logged

### Medium Priority
4. **Code Comments**
   - Add Doxygen-style comments to all classes/functions
   - Document parameters and return values
   - Add file-level documentation

5. **Test Different Configurations**
   - Test with various server counts
   - Test with different cycle counts
   - Verify scaling behavior

### Low Priority (Optional)
6. **Optional Feature**: Pre-sort streaming vs processing jobs
   - Not required but could be bonus points
   - Would require separate server pools

## 🎯 Grading Checklist

### Documentation (30%)
- [ ] Doxyfile created
- [ ] HTML documentation generated
- [ ] Documentation uploaded to people.tamu.edu
- [ ] All classes documented
- [ ] All functions documented
- [ ] File headers with descriptions

### Log and Completion (20%)
- [ ] Log file: `run_10servers_10000cycles.log` created
- [ ] Log shows 10,000 ticks
- [ ] Log shows scaling events
- [ ] Log shows queue management
- [ ] Log shows request processing

### Demonstration, Code, Git (50%)
- [ ] Code compiles without errors
- [ ] Code runs successfully
- [ ] Clean code structure
- [ ] Proper use of C++ features
- [ ] Git repository (optional but recommended)
- [ ] Live demonstration ready

## ✅ Final Verification

Run these commands to verify everything works:

```bash
# 1. Compile
make clean && make

# 2. Generate required log
echo -e "10\n10000" | ./load_balancer
cp logs/simulation.log logs/run_10servers_10000cycles.log

# 3. Verify log
wc -l logs/run_10servers_10000cycles.log  # Should be 10081 lines
grep "SCALE" logs/run_10servers_10000cycles.log | wc -l  # Should show scaling events

# 4. Test compilation
g++ -std=c++11 -Wall -Iinclude -c src/*.cpp  # Should compile cleanly
```

## 📊 Summary

**Overall Status**: ✅ **GOOD** - Core functionality is complete and working

**Main Issues**:
1. ✅ Job types fixed (was A-D, now S/P)
2. ⚠️ Doxygen documentation missing (30% of grade)
3. ⚠️ Need to generate specific log file name

**Recommendation**: 
- Code is functionally complete and well-structured
- Priority: Create Doxygen documentation immediately
- Generate the required log file
- Ready for submission after documentation is complete

