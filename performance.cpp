#include "performance.hpp"


    DPHViewer::DPHViewer(WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH]) {
        init();
        config(CounterPathBuffer);
        wcscpy_s(this->CounterPathBuffer,PDH_MAX_COUNTER_PATH, CounterPathBuffer);
    }
    double DPHViewer::getData()
    {
        if (inited == 0)init();
        if (inited == 0)return -1.0;
        Status = PdhCollectQueryData(Query);
        if (Status != ERROR_SUCCESS)
        {
            wprintf(L"\nPdhCollectQueryData failed with status 0x%x.", Status);
            destroy();
            return -1.0;
        }
        //
        // Compute a displayable value for the counter.
        //

        Status = PdhGetFormattedCounterValue(Counter,
            PDH_FMT_DOUBLE,
            &CounterType,
            &DisplayValue);
        if (Status != ERROR_SUCCESS)
        {
            wprintf(L"\nPdhGetFormattedCounterValue failed with status 0x%x.", Status);
            destroy();
            return -1.0;
        }
        return DisplayValue.doubleValue;
    }
     void DPHViewer::init()
    {
        Status = PdhOpenQuery(NULL, NULL, &Query);
        if (Status != ERROR_SUCCESS)
        {
            wprintf(L"\nPdhOpenQuery failed with status 0x%x.", Status);
            DPHViewer::destroy();
            return;
        }
        inited = 1;
    }
    void DPHViewer::config(WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH])
    {
        if (inited == 0)DPHViewer::init();
        if (inited == 0)return;
        // WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH] = L"\\Processor Information(_Total)\\Processor Frequency";
        Status = PdhAddCounter(Query, CounterPathBuffer, 0, &Counter);
        if (Status != ERROR_SUCCESS)
        {
            wprintf(L"\nPdhAddCounter failed with status 0x%x.", Status);
            DPHViewer::destroy();
            return;
        }
        //Collect Data.
        Status = PdhCollectQueryData(Query);
        if (Status != ERROR_SUCCESS)
        {
            wprintf(L"\nPdhCollectQueryData failed with 0x%x.\n", Status);
            DPHViewer::destroy();
            return;
        }
    }
    
     void DPHViewer::destroy()
    {
        if (Query)
        {
            PdhCloseQuery(Query);
        }
        inited = 0;
    }