#pragma once

class ExporterInterface{
public:
    virtual void doExport() = 0;
    virtual ~ExporterInterface() = default;
};