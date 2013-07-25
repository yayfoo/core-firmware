cd api
java -jar ../compiler/protoc-1.0M4.jar ../proto/chunk.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/chunk_received.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/event.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/function_call.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/function_return.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/hello.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/ignored.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/key_change.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/update_begin.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/update_done.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/update_ready.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/variable_request.proto
java -jar ../compiler/protoc-1.0M4.jar ../proto/variable_value.proto