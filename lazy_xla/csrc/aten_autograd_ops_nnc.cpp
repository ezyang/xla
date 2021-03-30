#include "lazy_xla/csrc/aten_autograd_ops_nnc.h"

#include "lazy_xla/csrc/aten_xla_type_default.h"  // move to cpp
#include "lazy_tensor_core/csrc/aten_xla_bridge.h"
#include "lazy_tensor_core/csrc/torch_util.h"

namespace torch_lazy_tensors {
namespace aten_autograd_ops_nnc {

torch::Tensor MaxPool2dAutogradFunctionNNC::forward(
    torch::autograd::AutogradContext* ctx, torch::Tensor self,
    torch::IntArrayRef kernel_size, torch::IntArrayRef stride,
    torch::IntArrayRef padding, torch::IntArrayRef dilation, bool ceil_mode) {
  ctx->saved_data["kernel_size"] = kernel_size;
  ctx->saved_data["stride"] = stride;
  ctx->saved_data["padding"] = padding;
  ctx->saved_data["dilation"] = dilation;
  ctx->saved_data["ceil_mode"] = ceil_mode;
  auto results = AtenXlaTypeDefault::max_pool2d_with_indices(
      self, kernel_size, stride, padding, dilation, ceil_mode);
  ctx->save_for_backward({self, std::get<1>(results)});
  return std::get<0>(results);
}

torch::autograd::variable_list MaxPool2dAutogradFunctionNNC::backward(
    torch::autograd::AutogradContext* ctx,
    torch::autograd::variable_list grad_output) {
  auto kernel_size = ctx->saved_data["kernel_size"].toIntList().vec();
  auto stride = ctx->saved_data["stride"].toIntList().vec();
  auto padding = ctx->saved_data["padding"].toIntList().vec();
  auto dilation = ctx->saved_data["dilation"].toIntList().vec();
  auto ceil_mode = ctx->saved_data["ceil_mode"].toBool();
  auto saved = ctx->get_saved_variables();
  auto self = saved[0];
  auto indices = saved[1];
  torch::Tensor grad = AtenXlaTypeDefault::max_pool2d_with_indices_backward(
      grad_output[0], self, kernel_size, stride, padding, dilation, ceil_mode,
      indices);

  torch::Tensor undef;
  torch::autograd::variable_list grad_inputs = {grad,  undef, undef,
                                                undef, undef, undef};
  return grad_inputs;
}

torch::Tensor MaxPool3dAutogradFunctionNNC::forward(
    torch::autograd::AutogradContext* ctx, torch::Tensor self,
    torch::IntArrayRef kernel_size, torch::IntArrayRef stride,
    torch::IntArrayRef padding, torch::IntArrayRef dilation, bool ceil_mode) {
  ctx->saved_data["kernel_size"] = kernel_size;
  ctx->saved_data["stride"] = stride;
  ctx->saved_data["padding"] = padding;
  ctx->saved_data["dilation"] = dilation;
  ctx->saved_data["ceil_mode"] = ceil_mode;
  auto results = AtenXlaTypeDefault::max_pool3d_with_indices(
      self, kernel_size, stride, padding, dilation, ceil_mode);
  ctx->save_for_backward({self, std::get<1>(results)});
  return std::get<0>(results);
}

torch::autograd::variable_list MaxPool3dAutogradFunctionNNC::backward(
    torch::autograd::AutogradContext* ctx,
    torch::autograd::variable_list grad_output) {
  auto kernel_size = ctx->saved_data["kernel_size"].toIntList().vec();
  auto stride = ctx->saved_data["stride"].toIntList().vec();
  auto padding = ctx->saved_data["padding"].toIntList().vec();
  auto dilation = ctx->saved_data["dilation"].toIntList().vec();
  auto ceil_mode = ctx->saved_data["ceil_mode"].toBool();
  auto saved = ctx->get_saved_variables();
  auto self = saved[0];
  torch::Tensor grad;
  auto indices = saved[1];
  grad = AtenXlaTypeDefault::max_pool3d_with_indices_backward(
      grad_output[0], self, kernel_size, stride, padding, dilation, ceil_mode,
      indices);

  torch::Tensor undef;
  torch::autograd::variable_list grad_inputs = {grad,  undef, undef,
                                                undef, undef, undef};
  return grad_inputs;
}

}  // namespace aten_autograd_ops_nnc
}  // namespace torch_lazy_tensors
