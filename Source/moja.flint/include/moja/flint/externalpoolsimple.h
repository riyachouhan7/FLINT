#pragma once

#include "moja/flint/_flint_exports.h"
#include "moja/flint/ipool.h"
#include "moja/flint/itransform.h"

#include <vector>

namespace moja::flint {

class FLINT_API ExternalPoolSimple : public IPool {
  public:
   ExternalPoolSimple() = delete;
   ExternalPoolSimple(std::vector<double>& pools, const std::string& name, const std::string& description,
                      const std::string& units, double scale, int order, int idx, std::shared_ptr<ITransform> initValue,
                      IPool* parent);

   ~ExternalPoolSimple() = default;

   const std::string& name() const override;
   const std::string& description() const override;
   const std::string& units() const override;
   double scale() const override;
   int order() const override;
   std::optional<double> initValue() const override;
   int idx() const override;

   double value() const override;
   void set_value(double value) override;

   void init() override;

   const IPool* parent() const override { return _parent; }
   const std::vector<const IPool*>& children() const override { return _children; }

   void add_child(IPool* pool) override;

   bool has_children() const override { return !_children.empty(); }
   bool is_child() const override { return _parent != nullptr; }

  protected:
   PoolMetaData _metadata;

   int _idx;
   std::shared_ptr<ITransform> _initValue;
   double& _value;

   IPool* _parent;
   std::vector<const IPool*> _children;
};

inline double ExternalPoolSimple::value() const { return _value; }

inline void ExternalPoolSimple::set_value(double value) { _value = value; }

inline int ExternalPoolSimple::idx() const { return _idx; }

}  // namespace moja::flint
