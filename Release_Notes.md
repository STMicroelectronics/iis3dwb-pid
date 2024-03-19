---
pagetitle: Release Notes for IIS3DWB Component
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for IIS3DWB Component Driver
Copyright &copy; 2021 STMicroelectronics\

[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# License

This software component is licensed by ST under BSD 3-Clause license, the "License".
You may not use this component except in compliance with the License. You may obtain a copy of the License at:

[BSD 3-Clause license](https://opensource.org/licenses/BSD-3-Clause)

# Purpose

This directory contains the IIS3DWB component drivers.
:::

::: {.col-sm-12 .col-lg-8}
# Update history

::: {.collapse}
<input type="checkbox" id="collapse-section1" aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">V1.0.0 / 18-June-2021</label>
<div>

## Main changes

### First release

- First official release [ref. DS v4.0]

##

</div>

<input type="checkbox" id="collapse-section2" aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">V1.1.0 / 01-June-2023</label>
<div>

## Main changes

- Fixes to PR #12
- Fix issues from static analysis of source code
- Fix typo in documentation of iis3dwb_fifo_status_get
- Add __weak directive to read/write registers routines
- iis3dwb_reg.c: fix some typos in the comments
- iis3dwb driver: fix potential array overflow in iis3dwb_fifo_out_raw_get
- iis3dwb_reg.h: Extend stmdev_ctx_t structure with mdelay callback
- iis3dwb driver: clean FIFO structure data and routines
- iis3dwb driver: improve FIFO routines and data
- repo name changed adding '-pid' extension.
- Fixed filt_xl_en_t #4

##

</div>

<input type="checkbox" id="collapse-section3" aria-hidden="true">
<label for="collapse-section3" aria-hidden="true">V1.1.1 / 24-July-2023</label>
<div>

## Main changes

- added user offset correction block (Fix: #15)

##

</div>

<input type="checkbox" id="collapse-section4" checked aria-hidden="true">
<label for="collapse-section4" aria-hidden="true">V2.0.0 / 19-Mar-2024</label>
<div>

## Main changes

- Add "const" to ctx arg for all APIs
- Fix wrong description for some functions

##

</div>
:::


:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation on IIS3DWB,
visit:
[IIS3DWB](https://www.st.com/content/st_com/en/products/mems-and-sensors/accelerometers/iis3dwb.html)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.0">Info</abbr>
:::
:::
</footer>
