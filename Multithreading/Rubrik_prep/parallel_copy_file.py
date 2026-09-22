import os
import threading
import math
from dataclasses import dataclass
from typing import Optional, BinaryIO
from concurrent.futures import ThreadPoolExecutor
import time


@dataclass
class CopyContext:
    """Thread-safe context for parallel file copying"""
    src_path: str
    dst_path: str
    file_size: int
    chunk_size: int
    next_offset: int = 0
    total_copied: int = 0
    error: Optional[Exception] = None
    lock: threading.Lock = threading.Lock()
    error_lock: threading.Lock = threading.Lock()
    progress_lock: threading.Lock = threading.Lock()


class ParallelFileCopier:
    """Parallel file copier with thread-safe chunking"""

    def __init__(self, chunk_size: int = 1024 * 1024):  # 1MB default
        self.chunk_size = chunk_size
        self.executor = None

    def _get_next_chunk(self, context: CopyContext) -> tuple[Optional[int], Optional[int]]:
        """Thread-safe method to get next chunk to process"""
        with context.lock:
            if context.next_offset >= context.file_size or context.error:
                return None, None

            offset = context.next_offset
            chunk_size = min(self.chunk_size, context.file_size - offset)
            context.next_offset += chunk_size
            return offset, chunk_size

    def _update_error(self, context: CopyContext, error: Exception):
        """Thread-safe error reporting"""
        with context.error_lock:
            if context.error is None:
                context.error = error

    def _update_progress(self, context: CopyContext, bytes_copied: int):
        """Thread-safe progress tracking"""
        with context.progress_lock:
            context.total_copied += bytes_copied

    def _copy_chunk(self, context: CopyContext, thread_id: int):
        """Worker function to copy a single chunk"""
        try:
            while True:
                # Get next chunk to process
                offset, size = self._get_next_chunk(context)
                if offset is None or size == 0:
                    break

                # Read chunk from source
                with open(context.src_path, 'rb') as src_file:
                    src_file.seek(offset)
                    data = src_file.read(size)

                if len(data) != size:
                    raise IOError(f"Read incomplete data: expected {size}, got {len(data)} bytes")

                # Write chunk to destination
                with open(context.dst_path, 'r+b') as dst_file:
                    dst_file.seek(offset)
                    dst_file.write(data)

                # Update progress
                self._update_progress(context, len(data))

                # Optional: print progress per thread
                if thread_id == 0:  # Only one thread reports
                    progress = (context.total_copied / context.file_size) * 100
                    print(f"\rProgress: {progress:.1f}%", end='')

        except Exception as e:
            self._update_error(context, e)

    def copy(self, src_path: str, dst_path: str, num_threads: int = 4) -> bool:
        """
        Copy file using multiple threads

        Args:
            src_path: Source file path
            dst_path: Destination file path
            num_threads: Number of parallel threads

        Returns:
            bool: True if copy succeeded, False otherwise
        """
        # Get file size
        try:
            file_size = os.path.getsize(src_path)
        except OSError as e:
            print(f"Error getting file size: {e}")
            return False

        # Validate parameters
        if file_size == 0:
            print("Warning: Source file is empty")
            with open(dst_path, 'wb') as f:
                pass  # Create empty file
            return True

        # Adjust chunk size for small files
        chunk_size = min(self.chunk_size, file_size)

        # Create destination file with same size
        try:
            with open(dst_path, 'wb') as f:
                f.seek(file_size - 1)
                f.write(b'\0')
        except OSError as e:
            print(f"Error creating destination file: {e}")
            return False

        # Initialize context
        context = CopyContext(
            src_path=src_path,
            dst_path=dst_path,
            file_size=file_size,
            chunk_size=chunk_size
        )

        print(f"Copying {src_path} ({file_size:,} bytes) to {dst_path}")
        print(f"Using {num_threads} threads with {chunk_size:,} byte chunks")

        start_time = time.time()

        # Use ThreadPoolExecutor for better thread management
        with ThreadPoolExecutor(max_workers=num_threads) as executor:
            # Submit tasks
            futures = []
            for i in range(num_threads):
                future = executor.submit(self._copy_chunk, context, i)
                futures.append(future)

            # Wait for completion
            for future in futures:
                future.result()

        # Check for errors
        if context.error:
            print(f"\nError during copy: {context.error}")
            try:
                os.remove(dst_path)  # Clean up partial copy
            except OSError:
                pass
            return False

        elapsed = time.time() - start_time
        speed = file_size / (1024 * 1024) / elapsed if elapsed > 0 else 0

        print(f"\nCopy completed successfully!")
        print(f"Time: {elapsed:.2f} seconds")
        print(f"Speed: {speed:.2f} MB/s")
        print(f"Total bytes copied: {context.total_copied:,}")

        return True

    def copy_with_progress_callback(self, src_path: str, dst_path: str,
                                    num_threads: int = 4,
                                    progress_callback=None) -> bool:
        """
        Copy with custom progress callback

        Args:
            progress_callback: Function that receives (copied_bytes, total_bytes)
        """
        # Same initialization as copy()
        try:
            file_size = os.path.getsize(src_path)
        except OSError as e:
            print(f"Error getting file size: {e}")
            return False

        chunk_size = min(self.chunk_size, file_size)

        with open(dst_path, 'wb') as f:
            f.seek(file_size - 1)
            f.write(b'\0')

        context = CopyContext(
            src_path=src_path,
            dst_path=dst_path,
            file_size=file_size,
            chunk_size=chunk_size
        )

        start_time = time.time()

        # Modified worker function with callback
        def copy_chunk_with_callback(context, thread_id):
            try:
                while True:
                    offset, size = self._get_next_chunk(context)
                    if offset is None or size == 0:
                        break

                    with open(context.src_path, 'rb') as src_file:
                        src_file.seek(offset)
                        data = src_file.read(size)

                    with open(context.dst_path, 'r+b') as dst_file:
                        dst_file.seek(offset)
                        dst_file.write(data)

                    self._update_progress(context, len(data))

                    # Call progress callback
                    if progress_callback and thread_id == 0:
                        progress_callback(context.total_copied, context.file_size)

            except Exception as e:
                self._update_error(context, e)

        # Execute copy
        threads = []
        for i in range(num_threads):
            thread = threading.Thread(target=copy_chunk_with_callback, args=(context, i))
            threads.append(thread)
            thread.start()

        # Wait for all threads
        for thread in threads:
            thread.join()

        if context.error:
            print(f"Error: {context.error}")
            try:
                os.remove(dst_path)
            except OSError:
                pass
            return False

        return True


def main():
    """Example usage"""
    import sys

    if len(sys.argv) < 3:
        print("Usage: python parallel_copy.py <source> <destination> [threads]")
        sys.exit(1)

    src = sys.argv[1]
    dst = sys.argv[2]
    threads = int(sys.argv[3]) if len(sys.argv) > 3 else 4

    # Check if source exists
    if not os.path.exists(src):
        print(f"Error: Source file '{src}' does not exist")
        sys.exit(1)

    # Create copier and copy
    copier = ParallelFileCopier(chunk_size=1024 * 1024)  # 1MB chunks

    # Simple progress callback
    def progress_callback(copied, total):
        percent = (copied / total) * 100
        print(f"\rProgress: {percent:.1f}% ({copied:,}/{total:,} bytes)", end='')

    # Choose copy method
    success = copier.copy_with_progress_callback(
        src, dst, threads, progress_callback
    )

    if success:
        print("\nDone!")
    else:
        print("\nFailed!")
        sys.exit(1)


if __name__ == "__main__":
    main()