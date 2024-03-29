#pragma once

#include <d3d12.h>
#include <wrl/client.h>

class DX12Helper
{
#pragma region Singleton
public:
	// Gets the one and only instance of this class
	static DX12Helper& GetInstance()
	{
		if (!instance)
		{
			instance = new DX12Helper();
		}

		return *instance;
	}

	// Remove these functions (C++ 11 version)
	DX12Helper(DX12Helper const&) = delete;
	void operator=(DX12Helper const&) = delete;

private:
	static DX12Helper* instance;
	DX12Helper() {};
#pragma endregion

public:
	~DX12Helper();

	// Initialization for singleton
	void Initialize(
		Microsoft::WRL::ComPtr<ID3D12Device> device,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue,
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator);
	// Command list & synchronization
	void CloseExecuteAndResetCommandList();
	/*
	Ensures our C++ code waits for the GPU to complete
	the command from the command list in the CloseExecuteAndResetCommandList()
	function above
	*/
	void WaitForGPU();

	// Resource creation
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateStaticBuffer(
		unsigned int dataStride,
		unsigned int dataCount,
		void* data);



private:
	// Overall device
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// Command list related
	// Note: We're assuming a single command list for the entire
	// engine at this point. That's not always true for more
	// complex engines but should be fine for now
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	// Basic CPU/GPU synchronization
	Microsoft::WRL::ComPtr<ID3D12Fence> waitFence;
	HANDLE waitFenceEvent;
	unsigned long waitFenceCounter;

};

